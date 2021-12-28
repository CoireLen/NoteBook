# Wt::Dbo 的实践介绍

## 绪论

Wt::Dbo 是一个 C++ ORM（对象关系映射）库。

该库作为Wt的一部分发布，用于构建数据库驱动的网络应用，但同样可以独立使用。

该库提供了一个基于类的数据库表视图，通过插入、更新和删除数据库记录，保持数据库对象的层次结构与数据库自动同步。C++类映射到数据库表，类字段映射到表列，指针和指针集合映射到数据库关系。一个来自映射类的对象被称为数据库对象（dbo）。查询结果可以用数据库对象、基元或这些基元的元组来定义。

一个现代的C++方法被用来解决映射的问题。我们没有采用基于XML的描述来说明C++类和字段应该如何映射到表和列上，也没有使用晦涩的宏，而是完全在C++代码中定义映射。

在本教程中，我们将通过一个博客的例子，类似于随库分发的例子。

> ![](./img-wtDbo/tip.png) 本教程中使用的例子的完整源代码可以在Wt的examples/feature/dbo/文件夹中作为可运行的程序提供。

## 映射一个单一的类

我们将首先使用Wt::Dbo将一个单一的类User映射到一个相应的表user。

> ![](./img-wtDbo/warning.png)在本教程和示例中，我们将命名空间Wt::Dbo别名为dbo，在解释中我们将直接引用该命名空间中可用的类型和方法。

为了构建下面的例子，你需要针对wtdbo和wtdbosqlite3库进行链接。

**映射一个单一的类（tutorial1.c）**

```cpp
#include <Wt/Dbo/Dbo.h>
#include <string>

namespace dbo = Wt::Dbo;

enum class Role {
    Visitor = 0,
    Admin = 1,
    Alien = 42
};

class User {
public:
    std::string name;
    std::string password;
    Role        role;
    int         karma;

    template<class Action>
    void persist(Action& a)
    {
        dbo::field(a, name,     "name");
        dbo::field(a, password, "password");
        dbo::field(a, role,     "role");
        dbo::field(a, karma,    "karma");
    }
};
```

这个例子展示了如何为一个C++类定义持久化支持。定义了一个模板成员方法 persist() ，作为该类的持久化定义。对于类中的每个成员，调用Wt::Dbo::field()来映射字段到表的列名。

正如你可能注意到的，标准的C++类型如int、std::string和enum类型很容易被库支持（支持的类型的完整列表可以在Wt::Dbo::sql_value_traits `<T>`的文档中找到）。对其他类型的支持可以通过专门化Wt::Dbo::sql_value_traits `<T>`来添加。还有对内置Wt类型的支持，如WDate、WDateTime、WTime和WString，可以通过包含<Wt/Dbo/WtSqlTraits.h>来启用。

该库定义了一些动作，这些动作将使用其persist()方法应用于数据库对象，该方法依次应用于其所有成员。然后，这些动作将读取、更新或插入数据库对象，创建模式，或传播交易结果。

> ![](./img-wtDbo/note.png)为了简洁起见，我们的例子使用了公共成员。没有什么可以阻止你将你的状态封装在私有成员中并提供访问器方法。你甚至可以通过区分读和写的动作，在访问器方法方面定义持久化方法。

## A first session

现在我们有了User类的映射定义，我们可以开始一个数据库会话，创建我们的模式（如果需要的话）并向数据库添加一个用户。

让我们来看看执行此操作的代码。

**(tutorial1.C continued)**

```
void run()
{
    /*
     * Setup a session, would typically be done once at application startup.
     */
    std::unique_ptr<dbo::backend::Sqlite3> sqlite3{new dbo::backend::Sqlite3("blog.db")};
    dbo::Session session;
    session.setConnection(std::move(sqlite3));

    ...
```

Session对象是一个长期存在的对象，它提供了对我们数据库对象的访问。你通常会在应用程序会话的整个生命周期内创建一个Session对象，并且每个用户创建一个。Wt::Dbo类中没有一个是线程安全的（除了连接池），而且会话对象在会话之间不能共享。

缺乏线程安全并不仅仅是我们懒惰的结果。它与数据库的事务完整性所做的承诺相吻合：当一个会话的事务还没有提交时，你不会想在另一个会话中看到它所做的修改（读-提交事务隔离级别）。然而，在未来实现一个写时复制的策略可能是有意义的，以允许在会话之间共享大量的数据库对象。

会话被赋予一个连接，它可以用来与数据库通信。会话只在交易过程中使用一个连接，因此并不真正需要一个专门的连接。当你计划使用多个并发会话时，使用一个连接池是有意义的，一个会话也可以通过对连接池的引用进行初始化。

Wt::Dbo使用一个抽象层来访问数据库，目前支持PostgreSQL、Sqlite3、MySQL和Firebird作为后端。

**(tutorial1.C continued)**

```cpp
    ...

    session.mapClass<User>("user");

    /*
     * Try to create the schema (will fail if already exists).
     */
    session.createTables();

    ...
```

接下来，我们使用mapClass()将每个数据库类注册到会话中，指出该类必须被映射到的数据库表。

当然，在开发过程中，以及在初始部署时，让Wt::Dbo创建或删除数据库模式是很方便的。

这就产生了以下[SQL]()语句。

```sql
begin transaction
create table "user" (
    "id" integer primary key autoincrement,
    "version" integer not null,
    "name" text not null,
    "password" text not null,
    "role" integer not null,
    "karma" integer not null
)
commit transaction
```

正如你所看到的，在映射到C++字段的四列旁边，默认情况下，Wt::Dbo添加了另外两列：id和version。id是一个代理主键，而version则用于基于版本的优化锁定。你也可以抑制版本字段，并提供任何类型的自然键来代替代理主键，见自定义映射。

最后，我们可以向数据库添加一个用户。所有的数据库操作都发生在一个事务中。

**(tutorial1.C continued)**

```cpp
  ...
    /*
     * A unit of work happens always within a transaction.
     */
    dbo::Transaction transaction{session};

    std::unique_ptr<User> user{new User()};
    user->name = "Joe";
    user->password = "Secret";
    user->role = Role::Visitor;
    user->karma = 13;

    dbo::ptr<User> userPtr = session.add(std::move(user));
}
```

对 Session::add() 的调用将一个对象添加到数据库。这个调用返回一个 ptr `<User>` 来引用一个 User 类型的数据库对象。这是一个共享指针，它也跟踪被引用对象的持久化状态。在每个会话中，一个数据库对象最多加载一次：会话跟踪已加载的数据库对象，并在对数据库的查询需要时返回一个现有对象。当数据库对象的最后一个指针超出范围时，数据库对象的暂存（内存中）副本也会被删除（除非它被修改过，在这种情况下，暂存副本只有在修改成功提交到数据库后才会被删除）。

会话还跟踪已经被修改的对象和需要被刷新（使用SQL语句）到数据库的对象。当提交事务时，或在需要保持暂存对象和数据库副本之间的一致性时（例如在进行查询之前），刷新会自动发生。

如果事务对象超出了范围，事务会自动提交。如果事务对象由于被抛出的异常而超出范围，事务将回滚。

```sql
begin transaction
insert into "user" ("version", "name", "password", "role", "karma")
    values (?, ?, ?, ?, ?)
commit transaction
```

所有的SQL语句都准备一次（每个连接），以后再使用，这样做的好处是避免了SQL注入问题，并允许潜在的更好的性能。

## 查询对象

有两种查询数据库的方法。可以使用Session::find `<Dbo>`(condition)来查询单个Dbo类的数据库对象。

**(tutorial1.C continued)**

```sql
dbo::ptr<User> joe = session.find<User>().where("name = ?").bind("Joe");

std::cerr << "Joe has karma: " << joe->karma << std::endl;
```

所有查询都使用带有位置参数绑定的准备好的语句。Session::find `<T>`() 方法返回一个 Query< ptr `<T>` > 对象。Query 对象可用于通过定义 SQL where、order by 和 group by 定义来细化搜索，并允许使用 Query::bind() 绑定参数。在这种情况下，查询应该期望有一个单一的结果，并被直接投射到数据库对象指针上。

> ![](./img-wtDbo/note.png)查询类有一个第二个参数BindStrategy，它有两个可能的值，对应于两种不同的查询实现。
>
> 默认策略是DynamicBinding，允许查询成为一个与会话相关的长期存在的对象，可以多次运行。它还允许你只通过改变顺序或限制/抵消来修改查询。
>
> 另一种策略是DirectBinding，它将绑定的参数直接传递给底层的准备语句。这样的查询只能运行一次，但由于参数值是直接传递给后端而不是存储在查询对象中，因此具有较少的（C++）开销的好处。

对数据库制定的查询是：

```sql
select id, version, "name", "password", "role", "karma"
    from "user"
    where (name = ?)
```

更普遍的查询方式是使用Session::query `<Result>`(sql)，它不仅支持数据库对象作为结果。上面的查询相当于：

```cpp
dbo::ptr<User> joe2 = session.query< dbo::ptr<User> >("select u from user u")
    .where("name = ?").bind("Joe");
```

这会生成类似的 SQL：

```sql
select u.id, u.version, u."name", u."password", u."role", u."karma"
    from user u
    where (name = ?)
```

传递给方法的sql语句可以是任意的sql，其返回的结果与结果类型兼容。SQL查询的选择部分可以被重写（如上面的例子）以返回被查询的数据库对象的各个字段。

为了说明Session::query `<Result>`()可用于返回其他类型，考虑下面的查询，其中返回一个int结果。

```sql
int count = session.query<int>("select count(1) from user")
    .where("name = ?").bind("Joe");
```

上面的查询是期望唯一的结果，但查询也可以有多个结果。因此，Session::query `<Result>`()一般可以返回一个dbo::collection `<Result>`（用于多个结果），在上面的例子中，为了方便，他们被强制为一个唯一的Result。类似地，Session::find `<Dbo>`()可以返回一个集合< ptr `<Dbo>`>或一个唯一的ptr `<Dbo>`。如果要求一个唯一的结果，但查询找到多个结果，将抛出NoUniqueResultException。

collection `<T>`是一个与STL兼容的集合，它的迭代器实现了InputIterator的要求。因此，你只能对一个集合的结果进行一次迭代。在结果被迭代之后，集合不能再被使用（但是查询对象可以被重复使用，除非使用了DirectBinding绑定策略）。

下面的代码显示了一个查询的多个结果是如何被迭代的。

```cpp
typedef dbo::collection< dbo::ptr<User> > Users;

Users users = session.find<User>();

std::cerr << "We have " << users.size() << " users:" << std::endl;

for (const dbo::ptr<User> &user : users)
    std::cerr << " user " << user->name
              << " with karma of " << user->karma << std::endl;
```

这段代码将执行两个数据库查询：一个用于调用collection::size()，另一个用于迭代结果。

```sql
select count(1) from "user"
select id, version, "name", "password", "role", "karma" from "user"
```

## 更新对象

不像其他大多数智能指针，ptr `<Dbo>`默认是只读的：它返回一个 const Dbo*。要修改一个数据库对象，你需要调用 ptr::modify() 方法，它返回一个非常量对象。这标志着该对象是脏的，修改的内容随后将被同步到数据库中。

```cpp
dbo::ptr<User> joe = session.find<User>().where("name = ?").bind("Joe");

joe.modify()->karma++;
joe.modify()->password = "public";
```

数据库同步并不是即时发生的。相反，它们被延迟，直到使用ptr `<Dbo>`::flush()或Session::flush()明确要求，直到执行一个查询，其结果可能会受到所做更改的影响，或直到事务被提交。

前面的代码将产生以下[SQL]()语句：

```sql
select "id", "version", "name", "password", "role", "karma"
    from "user"
    where (name = ?)
update "user"
    set "version" = ?, "name" = ?, "password" = ?, "role" = ?, "karma" = ?
    where "id" = ? and "version" = ?
```

我们已经看到了如何使用Session::add(ptr `<Dbo>`)，我们将一个新的对象添加到数据库中。相反的操作是 ptr `<Dbo>`::remove(): 它删除了数据库中的对象。

```cpp
dbo::ptr<User> joe = session.find<User>().where("name = ?").bind("Joe");

joe.remove();
```

在删除一个对象后，该暂存对象仍然可以使用，甚至可以重新添加到数据库中。

> ![](./img-wtDbo/note.png)和modify()一样，add()和remove()操作也推迟了与数据库的同步，因此下面的代码实际上并没有对数据库产生任何影响。
>
> ```cpp
> dbo::ptr<User> silly = session.add(std::unique_ptr<User>{new User()});
> silly.modify()->name = "Silly";
> silly.remove();
> ```

## 映射关系

### 多对一关系

让我们把帖子添加到我们的博客例子中，并在帖子和用户之间定义一个多对一的关系。在下面的代码中，我们把自己限制在对定义关系重要的语句上。

```cpp
#include <Wt/Dbo/Dbo.h>
#include <string>

namespace dbo = Wt::Dbo;

class User;

class Post {
public:
    ...

    dbo::ptr<User> user;

    template<class Action>
    void persist(Action& a)
    {
        ...

        dbo::belongsTo(a, user, "user");
    }
};

class User {
public:
    ...

    dbo::collection< dbo::ptr<Post> > posts;

    template<class Action>
    void persist(Action& a)
    {
        ...

        dbo::hasMany(a, posts, dbo::ManyToOne, "user");
    }
};
```

在Many-side，我们添加了一个对用户的引用，并在persist()方法中调用 belongsTo()。这使得我们可以引用这个帖子所属的用户。最后一个参数将对应于定义关系的数据库列的名称。

在单侧，我们添加一个帖子集合，并在persist()方法中调用hasMany()。连接字段必须与reciproce belongsTo()方法调用的名称相同。

如果我们使用Session::mapClass()将Post类添加到我们的会话中，并创建模式，会产生以下SQL：

```sql
create table "user" (
    ...

    -- table user is unaffected by the relationship
);

create table "post" (
    ...

    "user_id" bigint,
    constraint "fk_post_user" foreign key ("user_id") references "user" ("id") deferrable initially deferred
)
```

注意与连接名称 "user "相对应的user_id字段。

在Many-side，你可以读取或写入ptr来设置这个帖子所属的用户。

一方的集合允许我们检索所有相关的元素，也可以insert()和remove()元素，这与在多方设置ptr的效果相同。

**范例：**

```cpp
dbo::ptr<Post> post = session.add(std::unique_ptr<Post>{new Post()});
post.modify()->user = joe; // or joe.modify()->posts.insert(post);

// will print 'Joe has 1 post(s).'
std::cerr << "Joe has " << joe->posts.size() << " post(s)." << std::endl;
```

正如你所看到的，只要joe被设置为新帖子的用户，该帖子就会反映在joe的帖子集合中，反之亦然。

### 多对多关系

为了说明多对多的关系，我们将在我们的博客例子中添加标签，并在帖子和标签之间定义一个多对多的关系。在下面的代码中，我们再次将自己限制在对定义关系重要的语句上。

```cpp
#include <Wt/Dbo/Dbo.h>
#include <string>

namespace dbo = Wt::Dbo;

class Tag;

class Post {
public:
    ...

    dbo::collection< dbo::ptr<Tag> > tags;

    template<class Action>
    void persist(Action& a)
    {
        ...

        dbo::hasMany(a, tags, dbo::ManyToMany, "post_tags");
    }
};

class Tag {
public:
    ...

    dbo::collection< dbo::ptr<Post> > posts;

    template<class Action>
    void persist(Action& a)
    {
        ...

        dbo::hasMany(a, posts, dbo::ManyToMany, "post_tags");
    }
};
```

正如预期的那样，这种关系以几乎相同的方式反映在两个类中：它们都有一个相关类的数据库对象集合，在 persist() 方法中，我们调用 hasMany() 。在这种情况下，连接字段将对应于用于持久化关系的连接表的名称。

使用Session::mapClass()将Post类添加到我们的会话中，我们现在得到以下用于创建模式的SQL。

```sql
create table "post" (
    ...

    -- table post is unaffected by the relationship
)

create table "tag" (
    ...

    -- table tag is unaffected by the relationship
)

create table "post_tags" (
    "post_id" bigint not null,
    "tag_id" bigint not null,
    primary key ("post_id", "tag_id"),
    constraint "fk_post_tags_key1" foreign key ("post_id")
        references "post" ("id") on delete cascade deferrable initially deferred,
    constraint "fk_post_tags_key2" foreign key ("tag_id")
        references "tag" ("id") on delete cascade deferrable initially deferred
)

create index "post_tags_post" on "post_tags" ("post_id")
create index "post_tags_tag" on "post_tags" ("tag_id")
```

多对多关系两边的集合允许我们检索所有相关的元素。要定义一个帖子和一个标签之间的关系，你需要把帖子添加到标签的帖子集合，或者把标签添加到帖子的标签集合。你不可能同时做这两件事! 这一变化将自动反映在相互的集合中。同样地，要撤销一个帖子和一个标签之间的关系，你应该从帖子的标签集合中删除标签，或者从标签的帖子集合中删除帖子，但不能同时进行。

**范例:**

```cpp
dbo::ptr<Post> post = ...
dbo::ptr<Tag> cooking = session.add(std::unique_ptr<Tag>{new Tag()});
cooking.modify()->name = "Cooking";

post.modify()->tags.insert(cooking);

// will print '1 post(s) tagged with Cooking.'
std::cerr << cooking->posts.size() << " post(s) tagged with Cooking."
          << std::endl;
```

![](./img-wtDbo/warning.png)与上述相同的警告也适用于此。

### 一对一关系

让我们为我们的博客实例添加一个设置类，并在设置和用户之间定义一个一对一的关系。在下面的代码中，我们把自己限制在对定义关系重要的语句上。

```cpp
#include <Wt/Dbo/Dbo.h>
#include <string>

namespace dbo = Wt::Dbo;

class User;

class Settings {
public:
    ...

    dbo::ptr<User> user;

    template<class Action>
    void persist(Action& a)
    {
        ...

        dbo::belongsTo(a, user);
    }
};

class User {
public:
    ...

    dbo::weak_ptr<Settings> settings;

    template<class Action>
    void persist(Action& a)
    {
        ...

        dbo::hasOne(a, settings);
    }
};
```

尽管一对一的关系听起来是对称的，但它在数据库和Wt::Dbo中的实现却不是。在数据库中，这种关系是由一个表到另一个表的外键定义的（在我们的例子中，从设置到用户）。我们将通过说明一方是拥有的，另一方是拥有的来区分双方。

在拥有方，我们添加一个对用户的引用，并在persist()方法中调用 belongsTo()。这使得我们可以引用这些设置所属的用户。

在拥有方，我们为其设置添加一个弱引用，并在persist()方法中调用hasOne()。

如果我们使用Session::mapClass()将设置类添加到我们的会话中，并创建模式，就会产生以下SQL。

```sql
create table "user" (
    ...

    -- table user is unaffected by the relationship
);

create table "settings" (
    ...

    "user_id" bigint,
    constraint "fk_settings_user" foreign key ("user_id") references "user" ("id") deferrable initially deferred
)
```

在拥有方，我们使用 weak_ptr 来避免创建一个循环。weak_ptr实际上并不存储引用（也不存储底层数据库记录），而是以数据库查询的方式定义。这样做的结果是对它的任何操作都会涉及到查询。

在任何一方，你可以改变数值，这将更新关系的对等方。

**范例:**

```cpp
dbo::ptr<User> joe = session.find<User>().where("name = ?").bind("Joe");

dbo::ptr<Settings> settings = session.add(std::unique_ptr<Settings>{new Settings()});
settings.modify()->theme = "fancy-pink";
joe.modify()->settings = settings;

// will print 'Settings apply to Joe'
std::cerr << "Settings apply to " << settings->user->name << std::endl;
```

正如你所看到的，只要关系的一侧被修改，这也会反映在另一侧。

## 自定义映射

默认情况下，Wt::Dbo将为每个映射的表添加一个自动递增的代理主键（id）和一个版本字段（version）。

虽然这些默认值对一个新项目是有意义的，但你可以定制映射，这样你就可以映射到几乎任何现有的数据库模式。

### 更改或禁用代理主键“id”字段

要改变用于映射类的代理主键的字段名，或者禁用一个类的代理主键而使用自然键，你需要对Wt::Dbo::dbo_traits `<C>`进行专业化。

例如，下面的代码将类Post的主键字段从id改为post_id。

```cpp
#include <Wt/Dbo/Dbo.h>

namespace dbo = Wt::Dbo;

class Post {
public:
  ...
};

namespace Wt {
    namespace Dbo {

        template<>
        struct dbo_traits<Post> : public dbo_default_traits {
            static const char *surrogateIdField() {
                return "post_id";
            }
        };

    }
}
```

### 更改或禁用“版本”字段

要改变用于乐观的并发控制版本字段（version）的字段名，或者为一个类全部禁用乐观的并发控制，你需要将Wt::Dbo::dbo_traits `<C>`专业化。

例如，下面的代码禁用了Post类的乐观并发控制。

```cpp
#include <Wt/Dbo/Dbo.h>

namespace dbo = Wt::Dbo;

class Post {
public:
    ...
};

namespace Wt {
    namespace Dbo {

        template<>
        struct dbo_traits<Post> : public dbo_default_traits {
            static const char *versionField() {
                return 0;
            }
        };

    }
}
```
