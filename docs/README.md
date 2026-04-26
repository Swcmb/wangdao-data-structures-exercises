# 前端部署配置

本项目使用 GitHub Pages 部署前端展示页面，包含**完整的代码展示功能**。

## ✨ 功能特性

- 📖 **完整代码展示** - 所有 17 个 C 语言源文件，共 3200+ 行代码
- 🎨 **语法高亮** - 专业的代码语法高亮显示
- 📋 **行号显示** - 每行代码都带行号，方便阅读和引用
- 📊 **代码统计** - 实时显示文件行数和大小
- 🔗 **快速导航** - 按章节组织的文件树导航
- 📱 **响应式设计** - 支持桌面和移动端浏览
- 📋 **一键复制** - 支持一键复制完整代码
- 🔗 **GitHub 链接** - 直接跳转到源文件

## 📁 项目结构

```
docs/
├── index.html          # 主页面（包含代码展示功能）
├── styles.css          # 样式文件（现代化设计）
├── script.js           # JavaScript（导航、语法高亮）
├── code-data.js        # 嵌入的所有代码数据（自动生成）
├── build-embed.js      # 代码嵌入构建脚本
├── build.js            # 简易构建脚本
└── README.md           # 本部署说明
```

## 🚀 部署步骤

### 方法一：GitHub Actions 自动部署（推荐）

1. **启用 GitHub Pages**：
   - 访问仓库：https://github.com/Swcmb/wangdao-data-structures-exercises
   - 进入 **Settings** → **Pages**
   - 在 **Source** 下选择：**GitHub Actions**
   - 保存设置

2. **自动部署**：
   - 每次推送到 `main` 分支都会自动触发部署
   - 工作流会自动读取所有 `.c` 文件并嵌入到 `code-data.js`
   - 部署成功后会显示访问 URL

3. **手动触发部署**：
   - 进入仓库的 **Actions** 标签
   - 选择 **Deploy to GitHub Pages** workflow
   - 点击 **Run workflow** 按钮

### 方法二：本地构建后推送

```bash
# 1. 进入 docs 目录
cd docs

# 2. 运行构建脚本（生成 code-data.js）
node build-embed.js

# 3. 提交更改
git add .
git commit -m "build: 更新嵌入的代码数据"
git push

# 4. GitHub Actions 会自动部署
```

## 🌐 访问网站

部署成功后，可以通过以下地址访问：

```
https://Swcmb.github.io/wangdao-data-structures-exercises/
```

## 💻 本地预览

### 方法一：使用 Python

```bash
# 进入 docs 目录
cd docs

# 先生成代码数据
node build-embed.js

# 启动 HTTP 服务器
python3 -m http.server 8000

# 访问 http://localhost:8000
```

### 方法二：使用 Node.js

```bash
# 安装 http-server（全局安装）
npm install -g http-server

# 进入 docs 目录
cd docs

# 生成代码数据
node build-embed.js

# 启动服务器
http-server -p 8000

# 访问 http://localhost:8000
```

### 方法三：使用 VS Code Live Server

1. 安装 VS Code 的 **Live Server** 扩展
2. 打开 `docs/index.html`
3. 点击右下角 **Go Live** 按钮

## 📊 嵌入的代码内容

构建脚本会自动读取所有章节的 C 语言代码并嵌入到 `code-data.js` 文件中：

| 章节 | 文件数 | 内容 |
|------|--------|------|
| Chapter 02 | 7 个 | 顺序表、单链表、双链表、循环链表、静态链表 |
| Chapter 03 | 5 个 | 顺序栈、链栈、循环队列、链式队列、双端队列 |
| Chapter 04 | 1 个 | KMP 算法、串的基本操作 |
| Chapter 05 | 1 个 | 二叉树、线索二叉树、BST、AVL、哈夫曼树 |
| Chapter 06 | 1 个 | 图的遍历、最小生成树、最短路径、拓扑排序 |
| Chapter 07 | 1 个 | 顺序查找、折半查找、红黑树、B 树、散列查找 |
| Chapter 08 | 1 个 | 插入排序、交换排序、选择排序、归并排序、基数排序 |

## 🔧 自定义配置

### 修改网站标题

编辑 `docs/index.html` 中的 `<title>` 标签：

```html
<title>你的网站标题</title>
```

### 修改样式

编辑 `docs/styles.css` 文件，可以修改：
- 颜色变量（`:root` 部分）
- 布局样式
- 响应式断点
- 语法高亮颜色

### 添加新章节代码

当您在项目中添加新的 `.c` 文件后：

1. 确保文件放在对应的 `chapterX/` 目录中
2. 运行构建脚本：`node build-embed.js`
3. 提交并推送更改
4. GitHub Actions 会自动重新部署

## ⚙️ GitHub Actions 配置

工作流程文件位于 `.github/workflows/deploy-pages.yml`，包含：

- **触发条件**：
  - 推送到 main 分支的 `docs/**` 或 `chapter**/*.c` 文件
  - 手动触发（workflow_dispatch）

- **构建步骤**：
  1. 检出代码（完整历史记录）
  2. 设置 Node.js 环境
  3. 运行 `build-embed.js` 生成代码数据
  4. 配置 GitHub Pages
  5. 上传 docs 目录为 artifact
  6. 部署到 GitHub Pages

## 🐛 故障排查

### 部署失败

1. **检查 GitHub Actions 日志**：
   - 进入 Actions 标签查看详细的错误信息
   
2. **确认文件结构**：
   ```bash
   ls -la docs/
   ls -la chapter*/
   ```

3. **本地测试构建**：
   ```bash
   cd docs
   node build-embed.js
   ```

### 页面不更新

1. **清除浏览器缓存**：`Ctrl + Shift + R`（强制刷新）
2. **检查 GitHub Actions 是否成功完成**
3. **等待 CDN 刷新**（通常需要 1-2 分钟）

### 代码无法显示

1. **确认已运行构建脚本**：`code-data.js` 文件应该存在
2. **检查浏览器控制台**是否有 JavaScript 错误
3. **确认 `code-data.js` 已正确加载**（查看 Network 标签）

### 404 错误

1. **确认 GitHub Pages 已正确启用**
2. **检查仓库名称和 URL 是否匹配**
3. **等待部署完成**（通常需要 1-2 分钟）

## 🌍 自定义域名（可选）

如需使用自定义域名：

1. 在仓库的 **Settings** → **Pages** → **Custom domain** 中添加域名
2. 在域名 DNS 提供商处添加 CNAME 记录：
   ```
   CNAME Swcmb.github.io
   ```
3. 在 `docs/` 目录下创建 `CNAME` 文件，内容为你的域名：
   ```
   your-domain.com
   ```

## 📝 构建脚本说明

### build-embed.js

主要的构建脚本，功能：
- 读取所有 `chapterX/*.c` 文件
- 将代码内容嵌入到 `code-data.js`
- 生成文件统计信息（行数、大小）

### build.js

简易构建脚本，功能：
- 仅生成文件列表（不嵌入代码内容）
- 用于开发调试

## 📈 性能优化

- **代码嵌入**：所有代码直接嵌入到 JS 文件中，避免额外的 HTTP 请求
- **语法高亮**：客户端实时高亮，无需预先生成 HTML
- **按需加载**：仅渲染当前选中的文件内容
- **懒加载动画**：滚动时逐步显示章节卡片

## 🔐 安全注意事项

- 所有代码都是公开的 C 语言实现，不包含敏感信息
- 构建过程在 GitHub Actions 沙箱环境中运行
- 不收集任何用户数据

## 📚 相关资源

- [GitHub Pages 官方文档](https://docs.github.com/en/pages)
- [GitHub Actions 官方文档](https://docs.github.com/en/actions)
- [原项目仓库](https://github.com/Swcmb/wangdao-data-structures-exercises)
- [王道考研笔记链接](https://blog.csdn.net/weixin_43313333/article/details/129588429)

## 📄 许可证

CC 4.0 BY-SA

---

**提示**：如果您对代码展示功能有任何建议或发现问题，欢迎提交 Issue 或 Pull Request！
