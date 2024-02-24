# Linux SSHVPN

This program, runs a vpn like proxy on port 1080 on the client system using ssh in **LINUX**.
## Installation

If you are on any debian based repos, just Download the package from the releases and install it.

otherwise, build it yourself. i don't know!

# How to use

## Running the vpn

assume you want to connect to a vpn or server with this information:
- Host: sub.host.com
- UserName: user
- port: 4512
- **Optional** tunnel IP target (for example if you want to run the proxy tunnel on an IP except 127.0.0.1): 192.168.1.200

so you can run this command:

```bash
sshvpn user@sub.host.com:4512:192.168.1.200
```

**note** : if you leave the last ip address not assigned, proxy will run on 127.0.0.1. like this:

```bash
sshvpn user@sub.host.com:22
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


# Troubleshoot

After connecting to some servers, you may see this error:
```bash
Unable to negotiate with ***.***.***.*** port ****: no matching host key type found. Their offer: ssh-rsa,ssh-dss
```
I could solve this problem so my script would recognize it and connects with no problem, but sorry i don't have time and mood! so you can just normally go to:
```bash
~/.ssh
```
in the **config** file add this lines:
```bash
Host HOST_NAME
    HostKeyAlgorithms +ssh-rsa
    PubkeyAcceptedKeyTypes +ssh-rsa
```
replace the server IP or domain and save. enjoy!


# Contribute
just edit that main.c file.

# License

I don't know anything about this political stuff, feel free to use or change or anything you want.

Also you can modify the program to make it better, i will be happy merging your works :)
