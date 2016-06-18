#!/usr/bin/env sh

# 副本集A：A1 A2 A_arbiter
# 副本集B：B1 B2 B_arbiter
# 
# 服务器A: A1 B2
# 服务器B: B1 A1 A_arbiter B_arbiter

# 修改配置

# 单机多实例
apt-get install numactl

# 121.201.116.37 主节点
mkdir -p /var/lib/mongodb_27027 /var/lib/mongodb_27037

# 219.132.195.129 从节点 仲裁节点
mkdir -p /var/lib/mongodb_27027 /var/lib/mongodb_27127_arbiter /var/lib/mongodb_27037 /var/lib/mongodb_27137_arbiter

# 121.201.116.37 主节点
numactl --interleave=all /usr/bin/mongod --port=27027 --dbpath=/var/lib/mongodb_27027

# 219.132.195.129 从节点
numactl --interleave=all /usr/bin/mongod --port=27037 --dbpath=/var/lib/mongodb_27037

# 219.132.195.129 仲裁节点
numactl --interleave=all /usr/bin/mongod --port=27127 --dbpath=/var/lib/mongodb_27127_arbiter
numactl --interleave=all /usr/bin/mongod --port=27137 --dbpath=/var/lib/mongodb_27137_arbiter

# numactl --interleave=all /usr/bin/mongod –f /etc/mongodb/mongodb-27027.conf
# numactl --interleave=all /usr/bin/mongod –f /etc/mongodb/mongodb-27037.conf

# 配置副本集

use admin
config={_id:"ReplicaSet_27027",members:[{_id:0,host:"121.201.116.37:27027"},{_id:1,host:"219.132.195.129:27027",{_id:2,host:"219.132.195.129:27127","arbiterOnly":true}}]};
rs.initiate(config)

use admin
config={_id:"ReplicaSet_27037",members:[{_id:0,host:"121.201.116.37:27037"},{_id:1,host:"219.132.195.129:27037",{_id:2,host:"219.132.195.129:27137","arbiterOnly":true}}]};
rs.initiate(config)

# 启动config server

# 启动mongos

# 配置shard

# 停掉balancer
