interface Array<T> {
    reverse(): T[];
    sort(compareFn?: (a: T, b: T) => number): T[];
    // ... 
}

// map<U>(func: (value: T, index: number, array: T[]) => U, thisArg?: any): U[];


function numberToString(a: number[]) {
    var stringArray = a.map(v => v.toString());
    return stringArray;
}

numberToString([1, 2]);
