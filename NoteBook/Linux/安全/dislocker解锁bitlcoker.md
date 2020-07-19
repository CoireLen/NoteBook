# 使用Dislocker 解锁 BitLocker
```sh
su
dislocker -u -v -V /dev/sdbx /mnt/sdbx
mount -o loop,rw /mnt/sdbx/dislocker-file /mnt/sdbx-unlock
```
移除挂载
```sh
umount /mnt/sdbx-unlock
umount /mnt/sdbx
```