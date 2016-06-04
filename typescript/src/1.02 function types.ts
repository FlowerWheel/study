
function vote(candidate: string, callback: (result: string) => string) {
    callback(candidate);
}

vote("BigPig", (result) => {
    if (result === 'BigPig') {
        return 'shit';
    }
});
