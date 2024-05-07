要在 Markdown 中插入 HTML 格式的 Base64 图片，你需要使用 HTML 的 `<img>` 标签，并将 Base64 编码的图片数据作为 `src` 属性的值。下面是如何在 Markdown 中插入 HTML 格式的 Base64 图片的示例：

```markdown
![alt text](data:image/png;base64,<base64_encoded_image_data>)
```

在这个示例中：

- `data:image/png;base64,` 是固定的前缀，告诉浏览器这是一个 Base64 编码的图片数据，而不是一个图片文件的 URL。
- `<base64_encoded_image_data>` 是你要插入的图片的 Base64 编码数据。

## 使用Base64
Base64 是一种用于将二进制数据编码为 ASCII 字符的编码方法，通常用于在文本协议中传输二进制数据，或者用于在文本格式中存储二进制数据。在命令行中，可以使用 `base64` 命令来进行 Base64 编码和解码操作。

下面是一些 `base64` 命令的基本用法：

1. **Base64 编码**：将二进制文件或字符串编码为 Base64 格式。
   ```
   base64 <file>
   base64 <<< "your string"
   ```

2. **Base64 解码**：将 Base64 编码的数据解码为原始二进制数据。
   ```
   base64 -d <file>
   base64 -d <<< "base64 string"
   ```

3. **编码输出到文件**：将编码结果输出到文件中。
   ```
   base64 <file> -o <output_file>
   ```

4. **解码输出到文件**：将解码结果输出到文件中。
   ```
   base64 -d <file> -o <output_file>
   ```

5. **使用标准输入和标准输出**：可以使用管道将标准输入和标准输出与 `base64` 命令结合使用。
   ```
   echo "your string" | base64
   echo "base64 string" | base64 -d
   ```

这些是 `base64` 命令的一些基本用法。在实际应用中，您可以根据需要调整参数以满足特定的编码或解码需求。
