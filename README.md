# Linux SSHVPN

This program, runs a vpn like proxy on port 1080 on the client system using ssh in **LINUX**.
## Installation

I am working on it.

# How to use

## Running the vpn

assume you want to connect to a vpn or server with this information:
- Host: sub.host.com
- UserName: user
- port: 4512

so you can run this command:

```bash
sshvpn user@sub.host.com:4512
```

**note** : if the port is 22, you can leave it:

```bash
sshvpn user@sub.host.com
```

## Stopping the vpn
Just pass the kill argument:
```bash
sshvpn kill
```

## Get ssh process id
I also added an option, in case you want to know the process id that the ssh vpn is running on, And you don't have the patience to run `ps aux...` :
```bash
sshvpn pid
```
It prints something like this:
``SSH process ID: 59526``
## License

I don't know anything about this political stuff, feel free to use or change or anything you want.

Also you can modify the program to make it better, i will be happy merging your works :)
