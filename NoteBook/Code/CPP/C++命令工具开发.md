## 1.匹配argv
使用dimcli 库进行命令行匹配，与输出管理
```cpp
#include "dimcli/cli.h"
#include <iostream>
using namespace std;

int main(int argc, char * argv[]) {
    Dim::Cli cli;

    // Define option that populates an existing variable.
    int count;
    cli.opt(&count, "c n count", 1).desc("Times to say hello.");

    // Or, define option without referencing an existing variable. The variable
    // to populate is then implicitly allocated and the returned object is used
    // like a smart pointer to access it.
    auto & name = cli.opt<string>("name", "Unknown")
        .desc("Who to greet.");

    // Parse command line.
    if (!cli.parse(argc, argv))
        return cli.printError(cerr);

    // Access the options.
    if (!name)
        cout << "Greeting the unknown." << endl;
    for (int i = 0; i < count; ++i)
        cout << "Hello " << *name << "!" << endl;
    return 0;
}
```
运行与输出如下
```sh
$ a.out -x
Error: Unknown option: -x
$ a.out --help
Usage: a.out [OPTIONS]

Options:
  -c, -n, --count=NUM  Times to say hello. (default: 1)
  --name=STRING        Who to greet. (default: Unknown)

  --help               Show this message and exit.
$ a.out --count=2
Greeting the unknown.
Hello Unknown!
Hello Unknown!
$ a.out --name John
Hello John!
```

## 2. 进度条
[indicators](https://github.com/p-ranav/indicators)

```cpp
#include <indicators/progress_bar.hpp>
#include <thread>
#include <chrono>

int main() {
  using namespace indicators;
  ProgressBar bar{
    option::BarWidth{50},
    option::Start{"["},
    option::Fill{"="},
    option::Lead{">"},
    option::Remainder{" "},
    option::End{"]"},
    option::PostfixText{"Extracting Archive"},
    option::ForegroundColor{Color::green},
    option::FontStyles{std::vector<FontStyle>{FontStyle::bold}}
  };
  
  // Update bar state
  while (true) {
    bar.tick();
    if (bar.is_completed())
      break;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
```

## 3.使用JSON
使用Boost::json

