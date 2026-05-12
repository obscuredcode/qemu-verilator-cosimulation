#!/usr/bin/fish

./qemu-run -m 4G -enable-kvm -drive file=alpine.qcow2,media=disk -nic user -net user,hostfwd=tcp::2222-:22 -display sdl -device verilated -virtfs local,path=shared,mount_tag=shared,security_model=mapped-xattr