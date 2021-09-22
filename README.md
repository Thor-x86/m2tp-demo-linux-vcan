# M2TP Demo with Linux's Virtual CAN

> **WARNING:** You MUST [install M2TP](https://github.com/Thor-x86/m2tp#how-to-install) first!

## Download the source code

```bash
git clone https://github.com/Thor-x86/m2tp-demo-linux-vcan.git
cd m2tp-demo-linux-vcan
```

## Initialize the VCAN driver

```bash
./initialize.bash
```

## Build the source code

```bash
make
```

## Run `leader` Side

```bash
./leader
```

## Run `member` Side

```bash
./member
```
