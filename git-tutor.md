git-tutor
=========

### git config

### init a git store

```bash
git init
git status
git add README.md
git commit -m 'First Commit'
git log
```

### use ssh

使用过Git的朋友都知道每次提交时(HTTPS)都需要输入用户名和密码，这是一个很低效的开发过程。（虽然有时可以让开发人员减少push的次数）。
其实，在最开始Github上面仅能使用SSH可以免输用户名。今天，我们来看看如何配置SSH生成RSA KEY。

* 备份.ssh文件夹（在用户文件夹下）的内容

```bash
cd <用户文件夹>/.ssh
```

* 生成RSA密钥
    这样在<用户文件夹>/.ssh下得到两个文件：id_rsa和id_rsa.pub

```bash
ssh-keygen -t rsa -C "邮箱"
```

* 把密钥添加到ssh

```bash
ssh-add github_rsa
```

* 关联SSH

登陆Github官网。通过右上角导航，进入设置，在左方选择SSH, 增加SSH, 并把id_rsa.pub文件的内容复制至内容框，提交。

* 查看当前推送方法

```bash
$ git remote -v
```
    origin https://github.com/someaccount/someproject.git (fetch)
    origin https://github.com/someaccount/someproject.git (push)

* 修改

```bash
$ git remote set-url origin git@github.com:someaccount/someproject.git
```
