var Promise = require("bluebird");
var fs = Promise.promisifyAll(require("fs"));
var _ = require("lodash");
var path = require("path");
var util = require("util");

function directorySizeInfo(root, visit) {
  visit = visit || _.noop;
  var counts = {dirs: 0, files: 0};
  var stats = (function reader(root) {
    return fs.readdirAsync(root).map(function(fileName) {
      var filePath = path.join(root, fileName);
      return fs.statAsync(filePath).then(function(stat) {
        stat.filePath = filePath;
        if (stat.isDirectory()) {
          counts.dirs++;
          return reader(filePath)
        }
        counts.files++;
        visit(filePath, stat);
        return stat;
      });
    }).then(_.flatten);
  })(root).then(_);

  var totalSize = stats.call("pluck", "size").call("reduce", function(a, b) {
    return a + b;
  }, 0);

  return Promise.props({
    counts: counts,
    totalSize: totalSize
  });
}

directorySizeInfo(process.argv[2] || ".").then(function(sizeInfo) {
  console.log(util.format(" %d directories, %d files Total size: %d bytes", sizeInfo.counts.dirs, sizeInfo.counts.files, sizeInfo.totalSize));
});
