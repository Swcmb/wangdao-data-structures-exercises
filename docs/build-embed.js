const fs = require('fs');
const path = require('path');

const docsDir = path.join(__dirname);
const rootDir = path.join(docsDir, '..');
const chapterDirs = [
    'chapter2', 'chapter3', 'chapter4', 
    'chapter5', 'chapter6', 'chapter7', 'chapter8'
];

const CODE_DATA = {};

console.log('正在读取并嵌入所有代码文件...\n');

chapterDirs.forEach(chapter => {
    const chapterPath = path.join(rootDir, chapter);
    
    if (!fs.existsSync(chapterPath)) {
        console.log(`跳过不存在的目录：${chapter}`);
        return;
    }
    
    const files = fs.readdirSync(chapterPath)
        .filter(file => file.endsWith('.c'));
    
    CODE_DATA[chapter] = {
        title: getChapterTitle(chapter),
        files: []
    };
    
    files.forEach(fileName => {
        const filePath = path.join(chapterPath, fileName);
        const content = fs.readFileSync(filePath, 'utf-8');
        
        CODE_DATA[chapter].files.push({
            name: fileName,
            path: `${chapter}/${fileName}`,
            content: content,
            lines: content.split('\n').length,
            size: Buffer.byteLength(content, 'utf8')
        });
        
        console.log(`  ✓ ${fileName}: ${content.split('\n').length} 行`);
    });
    
    console.log(`✓ ${chapter}: ${files.length} 个文件\n`);
});

const dataJsContent = `// 自动生成 - 包含所有代码数据
const CODE_DATA = ${JSON.stringify(CODE_DATA, null, 2)};

if (typeof module !== 'undefined' && module.exports) {
    module.exports = CODE_DATA;
}
`;

const dataPath = path.join(docsDir, 'code-data.js');
fs.writeFileSync(dataPath, dataJsContent, 'utf-8');

console.log(`✓ 生成 code-data.js (${(Buffer.byteLength(dataJsContent, 'utf8') / 1024).toFixed(1)} KB)`);
console.log('\n构建完成！所有代码已嵌入到 code-data.js 文件中');

function getChapterTitle(chapterNum) {
    const titles = {
        'chapter2': '第二章：线性表',
        'chapter3': '第三章：栈和队列',
        'chapter4': '第四章：串',
        'chapter5': '第五章：树',
        'chapter6': '第六章：图',
        'chapter7': '第七章：查找',
        'chapter8': '第八章：排序'
    };
    return titles[chapterNum] || chapterNum;
}
