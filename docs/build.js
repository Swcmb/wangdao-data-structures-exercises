const fs = require('fs');
const path = require('path');

const docsDir = path.join(__dirname);
const chapterDirs = [
    'chapter2', 'chapter3', 'chapter4', 
    'chapter5', 'chapter6', 'chapter7', 'chapter8'
];

const FILES_DATA = {};

console.log('正在读取代码文件...');

chapterDirs.forEach(chapter => {
    const chapterPath = path.join(docsDir, '..', chapter);
    
    if (!fs.existsSync(chapterPath)) {
        console.log(`跳过不存在的目录：${chapter}`);
        return;
    }
    
    const files = fs.readdirSync(chapterPath)
        .filter(file => file.endsWith('.c'));
    
    if (files.length > 0) {
        FILES_DATA[chapter] = {
            title: getChapterTitle(chapter),
            files: files.map(name => ({
                name,
                path: `../${chapter}/${name}`
            }))
        };
        console.log(`✓ 读取 ${chapter}: ${files.length} 个文件`);
    }
});

const scriptPath = path.join(docsDir, 'script.js');
let scriptContent = fs.readFileSync(scriptPath, 'utf-8');

const filesDataRegex = /const FILES_DATA = \{[\s\S]*?\};/;
const newFilesData = `const FILES_DATA = ${JSON.stringify(FILES_DATA, null, 4)};`;

scriptContent = scriptContent.replace(filesDataRegex, newFilesData);
fs.writeFileSync(scriptPath, scriptContent, 'utf-8');

console.log('✓ 已更新 script.js 中的文件数据');
console.log('构建完成！');

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
