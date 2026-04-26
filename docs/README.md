# 前端部署配置

本项目使用 GitHub Pages 部署前端展示页面。

## 部署步骤

### 1. 启用 GitHub Pages

1. 访问仓库：https://github.com/Swcmb/wangdao-data-structures-exercises
2. 进入 **Settings** → **Pages**
3. 在 **Source** 下选择：
   - **Build and deployment** 选择：GitHub Actions
4. 保存设置

### 2. 自动部署

配置完成后，每次推送到 `main` 分支的 `docs/` 目录的更改都会自动触发部署。

也可以手动触发部署：
1. 进入仓库的 **Actions** 标签
2. 选择 **Deploy to GitHub Pages** workflow
3. 点击 **Run workflow** 按钮
4. 选择分支后运行

### 3. 访问网站

部署成功后，可以通过以下地址访问：

```
https://Swcmb.github.io/wangdao-data-structures-exercises/
```

## 本地预览

在本地开发时，可以使用以下方法预览：

```bash
# 使用 Python 内置服务器
cd docs
python3 -m http.server 8000

# 然后访问 http://localhost:8000
```

或者使用 Node.js：

```bash
# 安装 http-server（全局安装）
npm install -g http-server

# 启动服务器
cd docs
http-server

# 然后访问 http://localhost:8080
```

## 文件结构

```
docs/
├── index.html          # 主页面
├── styles.css          # 样式文件
├── script.js           # JavaScript 脚本
└── README.md           # 部署说明
```

## 自定义内容

### 修改页面标题

编辑 `docs/index.html` 中的 `<title>` 标签：

```html
<title>你的网站标题</title>
```

### 修改样式

编辑 `docs/styles.css` 文件，可以修改：
- 颜色变量（`:root` 部分）
- 布局样式
- 响应式断点

### 添加新章节

在 `docs/index.html` 的 `chapters-grid` 部分添加新的 `chapter-card`：

```html
<div class="chapter-card" data-chapter="9">
    <div class="chapter-number">09</div>
    <h3 class="chapter-title">新章节标题</h3>
    <ul class="chapter-list">
        <li>内容 1</li>
        <li>内容 2</li>
    </ul>
</div>
```

## GitHub Actions 配置

工作流程文件位于 `.github/workflows/deploy-pages.yml`，包含：

- **触发条件**：推送到 main 分支或手动触发
- **部署环境**：github-pages
- **构建步骤**：
  1. 检出代码
  2. 配置 Pages
  3. 上传 docs 目录为 artifact
  4. 部署到 GitHub Pages

## 故障排查

### 部署失败

1. 检查 GitHub Actions 日志
2. 确认 `docs/` 目录存在且包含 `index.html`
3. 确认 workflow 文件语法正确

### 页面不更新

1. 清除浏览器缓存（Ctrl + Shift + R）
2. 检查 GitHub Actions 是否成功完成
3. 等待几分钟让 CDN 刷新

### 404 错误

1. 确认 GitHub Pages 已正确启用
2. 检查仓库名称和 URL 是否匹配
3. 等待部署完成（通常需要 1-2 分钟）

## 自定义域名（可选）

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

## 许可证

CC 4.0 BY-SA

## 相关链接

- [GitHub Pages 文档](https://docs.github.com/en/pages)
- [GitHub Actions 文档](https://docs.github.com/en/actions)
- [原项目仓库](https://github.com/Swcmb/wangdao-data-structures-exercises)
