#生成 #编译 

[生成最小的Rust二进制文件](https://github.com/johnthagen/min-sized-rust)
该存储库演示了如何最小化 Rust 二进制文件的大小。
默认情况下，Rust 会针对执行速度、编译速度和调试简易性进行优化，而不是针对二进制大小进行优化，因为对于绝大多数应用程序来说，这是理想的选择。但对于开发人员想要优化二进制大小的情况，Rust 提供了实现此目的的机制。

## 在  Release 模式编译
默认情况下，cargo build 会以调试模式构建 Rust 二进制文件。调试模式禁用了许多优化，这有助于调试器（以及运行调试器的集成开发环境）提供更好的调试体验。调试二进制文件可能比发布二进制文件大 30% 或更多。
要尽量减小二进制文件的大小，请在发布模式下构建：
```sh
 $ cargo build --release
 ```

### strip 定义符号
在 Linux 和 macOS 上，默认情况下，编译后的 .elf 文件中包含符号信息。正确执行二进制文件并不需要这些信息。
可以对 Cargo 进行配置，使其自动剥离二进制文件。请按此方式修改 Cargo.toml：
```toml
[profile.release]
strip = true  # 自动从二进制文件中剥离符号。
```

在 Rust 1.59 之前，可直接在 .elf 文件上运行 strip：

```sh
$ strip target/release/min-sized-rust
```

### 针对编译文件尺寸优化

在发布版本时，Cargo 默认将优化级别设为 3，这将优化二进制文件的速度。要指示 Cargo 优化二进制文件的最小尺寸，请使用 Cargo.toml 中的 z 优化级别：

```toml
[profile.release]
opt-level = "z"  # Optimize for size.
```

> [!Note]
> 在某些情况下，“s ”级可能会比 “z ”级产生更小的二进制文件，这在选项级文档中有解释：
建议尝试使用不同的级别，以找到适合自己项目的平衡点。可能会出现令人惊讶的结果，例如...... “s ”和 “z ”级并不一定更小。

### 启用链路时间优化 (LTO)

默认情况下，Cargo 会指示编译单元单独进行编译和优化。LTO 会指示链接器在链接阶段进行优化。例如，这可以删除死代码，通常还能减小二进制文件的大小。

在 Cargo.toml 中启用 LTO：
```toml
[profile.release]
lto = true
```

### 减少并行代码生成单元，提高优化程度

默认情况下，Cargo 为发布版本指定了 16 个并行代码生成单元。这可以缩短编译时间，但会妨碍某些优化。
请在 Cargo.toml 中将此值设为 1，以最大限度地减少优化的大小：

```toml
[profile.release]
codegen-units = 1
```

### 恐慌时中止
> [!Important]
> 到此为止，所讨论的减少二进制文件大小的功能对程序的行为（仅是执行速度）并无影响。该功能确实会对程序的运行产生影响。

默认情况下，当 Rust 代码遇到必须调用 panic!() 的情况时，它会展开堆栈并生成有用的回溯。可以指示 rustc 立即终止而不是展开，这样就不需要额外的展开代码了。

在 Cargo.toml 中启用此功能：
```toml
[profile.release]
panic = "abort"
```

### 删除报错位置信息

默认情况下，Rust 会包含 panic!() 和 [track_caller] 的文件、行和列信息，以提供更有用的回溯信息。这些信息需要占用二进制文件的空间，因此增加了编译后二进制文件的大小。
要删除这些文件、行和列信息，请使用不稳定的 rustc -Zlocation-detail 标志：

```sh
$ RUSTFLAGS="-Zlocation-detail=none" cargo +nightly build --release
```

### 移除 fmt::debug
使用 -Zfmt-debug 标志，可以将 #[derive(Debug)] 和 {:?} 格式化变为无效。这将破坏 dbg!()、assert!()、unwrap() 等函数的输出，并可能破坏不明智地依赖调试格式的代码，但会删除派生的 fmt 函数及其字符串。

```sh
$ RUSTFLAGS="-Zfmt-debug=none" cargo +nightly build --release
```

### 使用 build-std 优化 libstd

Rust 附带了标准库 (libstd) 及其工具链的预构建副本。这意味着开发人员不需要在每次构建应用程序时都构建 libstd。 libstd 被静态链接到二进制文件中。
虽然这非常方便，但如果开发人员试图积极优化大小，则会存在一些缺点。
1.预构建的 libstd 针对速度而非大小进行了优化。
2.无法删除 libstd 中未在特定应用程序中使用的部分（例如 LTO 和恐慌行为）。
这就是 build-std 的用武之地。build-std 功能能够从源代码使用您的应用程序编译 libstd。它使用 rustup 方便提供的 rust-src 组件来完成此操作。
安装适当的工具链和 rust-src 组件：
```sh
$ rustup toolchain install nightly
$ rustup component add rust-src --toolchain nightly
```
使用 build-std 构建：
```sh
# Find your host's target triple.
$ rustc -vV
...
host: x86_64-apple-darwin

# Use that target triple when building with build-std.
# Add the =std,panic_abort to the option to make panic = "abort" Cargo.toml option work.
# See: https://github.com/rust-lang/wg-cargo-std-aware/issues/56
$ RUSTFLAGS="-Zlocation-detail=none -Zfmt-debug=none" cargo +nightly build \
  -Z build-std=std,panic_abort \
  -Z build-std-features="optimize_for_size" \
  --target x86_64-apple-darwin --release
```

optimize_for_size 标志为 libstd 提供了一个提示，即它应尽量使用针对二进制大小优化的算法。有关它的更多信息，请参阅跟踪问题。
在 macOS 上，最终剥离的二进制文件大小减至 51KB。