const CHAPTERS_DATA = CODE_DATA || {};
const TOTAL_FILES = Object.values(CHAPTERS_DATA).reduce((sum, chapter) => sum + chapter.files.length, 0);
const TOTAL_LINES = Object.values(CHAPTERS_DATA).reduce((sum, chapter) => {
    return sum + chapter.files.reduce((fileSum, file) => fileSum + file.lines, 0);
}, 0);

let currentFile = null;

document.addEventListener('DOMContentLoaded', function() {
    initNavigation();
    initFileTree();
    initQuickLinks();
    initOverviewCards();
    initCopyButton();
    updateStats();
});

function initNavigation() {
    const navLinks = document.querySelectorAll('.nav-link');
    const views = {
        'overview': document.getElementById('view-overview'),
        'chapters': document.getElementById('view-chapters')
    };
    
    navLinks.forEach(link => {
        const viewName = link.getAttribute('data-view');
        if (!viewName) return;
        
        link.addEventListener('click', function(e) {
            e.preventDefault();
            
            navLinks.forEach(l => l.classList.remove('active'));
            link.classList.add('active');
            
            Object.keys(views).forEach(key => {
                views[key].classList.remove('active');
            });
            
            if (views[viewName]) {
                views[viewName].classList.add('active');
            }
        });
    });
}

function initFileTree() {
    const fileTree = document.getElementById('file-tree');
    if (!fileTree) return;
    
    fileTree.innerHTML = '';
    
    Object.keys(CHAPTERS_DATA).forEach(chapterKey => {
        const chapter = CHAPTERS_DATA[chapterKey];
        
        const group = document.createElement('div');
        group.className = 'file-group';
        
        const header = document.createElement('div');
        header.className = 'file-group-header';
        header.innerHTML = `
            <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" class="folder-icon">
                <path d="M22 19a2 2 0 0 1-2 2H4a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h5l2 3h9a2 2 0 0 1 2 2z"></path>
            </svg>
            <span class="file-group-title">${chapter.title}</span>
            <span class="file-count-badge">${chapter.files.length}</span>
        `;
        
        const fileList = document.createElement('ul');
        fileList.className = 'file-list';
        
        chapter.files.forEach(file => {
            const item = document.createElement('li');
            item.className = 'file-item';
            item.innerHTML = `
                <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" class="file-icon">
                    <path d="M13 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V9z"></path>
                    <polyline points="13 2 13 9 20 9"></polyline>
                </svg>
                <span class="file-name-text">${file.name}</span>
            `;
            
            item.addEventListener('click', function() {
                loadFile(file, chapterKey);
                
                document.querySelectorAll('.file-item').forEach(i => i.classList.remove('active'));
                item.classList.add('active');
            });
            
            fileList.appendChild(item);
        });
        
        group.appendChild(header);
        group.appendChild(fileList);
        fileTree.appendChild(group);
    });
}

function loadFile(file, chapterKey) {
    const codeDisplay = document.getElementById('code-display');
    const fileNameEl = document.getElementById('current-file');
    const filePathEl = document.getElementById('file-path');
    const githubBtn = document.getElementById('github-file-btn');
    const lineCountEl = document.getElementById('line-count');
    const fileSizeEl = document.getElementById('file-size');
    
    fileNameEl.textContent = file.name;
    filePathEl.textContent = file.path;
    githubBtn.href = `https://github.com/Swcmb/wangdao-data-structures-exercises/blob/main/${file.path}`;
    
    const code = file.content;
    codeDisplay.innerHTML = syntaxHighlight(code);
    currentFile = { content: code, name: file.name, path: file.path };
    
    lineCountEl.textContent = file.lines;
    fileSizeEl.textContent = formatFileSize(file.size);
}

function syntaxHighlight(code) {
    const escaped = escapeHtml(code);
    
    let highlighted = escaped
        .replace(/\b(auto|break|case|const|continue|default|do|else|enum|extern|for|goto|if|register|return|sizeof|static|struct|switch|typedef|union|volatile|while|inline|restrict|_Bool|_Complex|_Imaginary)\b/g, '<span class="syntax-keyword">$1</span>')
        .replace(/\b(int|char|float|double|void|short|long|signed|unsigned|size_t|NULL|true|false|bool)\b/g, '<span class="syntax-type">$1</span>')
        .replace(/("(?:[^"\\]|\\.)*")/g, '<span class="syntax-string">$1</span>')
        .replace(/('(?:[^'\\]|\\.)*')/g, '<span class="syntax-string">$1</span>')
        .replace(/(\/\/.*$)/gm, '<span class="syntax-comment">$1</span>')
        .replace(/(\/\*[\s\S]*?\*\/)/g, '<span class="syntax-comment">$1</span>')
        .replace(/\b(\d+)\b/g, '<span class="syntax-number">$1</span>')
        .replace(/\b([a-zA-Z_]\w*)\s*\(/g, '<span class="syntax-function">$1</span>(')
        .replace(/#\s*(include|define|ifdef|ifndef|if|endif|else|undef|pragma)/g, '<span class="syntax-preprocessor">#$1</span>');
    
    const lines = highlighted.split('\n');
    const numberedLines = lines.map((line, index) => {
        const lineNum = index + 1;
        return `<div class="line"><span class="line-number">${lineNum.toString().padStart(3, ' ')}</span> ${line || ' '}</div>`;
    });
    
    return numberedLines.join('\n');
}

function escapeHtml(text) {
    const div = document.createElement('div');
    div.textContent = text;
    return div.innerHTML;
}

function formatFileSize(bytes) {
    if (bytes < 1024) {
        return bytes + ' B';
    } else if (bytes < 1024 * 1024) {
        return (bytes / 1024).toFixed(1) + ' KB';
    } else {
        return (bytes / (1024 * 1024)).toFixed(1) + ' MB';
    }
}

function initQuickLinks() {
    const quickLinks = document.querySelectorAll('.quick-link');
    quickLinks.forEach(link => {
        link.addEventListener('click', function(e) {
            e.preventDefault();
            const chapter = this.getAttribute('data-chapter');
            
            document.querySelectorAll('.nav-link').forEach(l => l.classList.remove('active'));
            document.querySelector('[data-view="chapters"]').classList.add('active');
            
            document.getElementById('view-overview').classList.remove('active');
            document.getElementById('view-chapters').classList.add('active');
            
            setTimeout(() => {
                const chapterKey = 'chapter' + chapter;
                const firstFile = CHAPTERS_DATA[chapterKey]?.files[0];
                if (firstFile) {
                    const fileItems = document.querySelectorAll('.file-item');
                    fileItems.forEach(item => {
                        if (item.textContent.includes(firstFile.name)) {
                            item.click();
                            item.scrollIntoView({ behavior: 'smooth', block: 'center' });
                        }
                    });
                }
            }, 100);
        });
    });
}

function initOverviewCards() {
    const cards = document.querySelectorAll('.chapter-overview-card');
    cards.forEach(card => {
        card.addEventListener('click', function() {
            const chapter = this.getAttribute('data-chapter');
            
            const quickLink = document.querySelector(`.quick-link[data-chapter="${chapter}"]`);
            if (quickLink) {
                quickLink.click();
            }
        });
    });
}

function initCopyButton() {
    const copyBtn = document.getElementById('copy-btn');
    if (!copyBtn) return;
    
    copyBtn.addEventListener('click', async function() {
        if (!currentFile || !currentFile.content) {
            showToast('请先选择要复制的代码文件');
            return;
        }
        
        try {
            await navigator.clipboard.writeText(currentFile.content);
            showToast('代码已复制到剪贴板！');
        } catch (error) {
            const textArea = document.createElement('textarea');
            textArea.value = currentFile.content;
            document.body.appendChild(textArea);
            textArea.select();
            document.execCommand('copy');
            document.body.removeChild(textArea);
            showToast('代码已复制到剪贴板！');
        }
    });
}

function showToast(message) {
    const toast = document.getElementById('toast');
    if (!toast) return;
    
    toast.textContent = message;
    toast.classList.add('show', 'toast-copy');
    
    setTimeout(() => {
        toast.classList.remove('show', 'toast-copy');
    }, 2000);
}

function updateStats() {
    const stats = {
        chapters: Object.keys(CHAPTERS_DATA).length,
        files: TOTAL_FILES,
        lines: TOTAL_LINES,
        algorithms: '50+'
    };
    
    const chapterEl = document.getElementById('total-chapters');
    const filesEl = document.getElementById('total-files');
    const linesEl = document.getElementById('total-lines');
    const algorithmsEl = document.getElementById('total-algorithms');
    
    if (chapterEl) chapterEl.textContent = stats.chapters;
    if (filesEl) filesEl.textContent = stats.files;
    if (linesEl) linesEl.textContent = stats.lines.toLocaleString();
    if (algorithmsEl) algorithmsEl.textContent = stats.algorithms;
}

if (typeof module !== 'undefined' && module.exports) {
    module.exports = { CHAPTERS_DATA, TOTAL_FILES, TOTAL_LINES };
}
