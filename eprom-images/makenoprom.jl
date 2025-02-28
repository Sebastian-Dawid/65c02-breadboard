function write_byte(addr, rom, byte)
    rom[addr + 1] = byte
end

nop = ones(UInt8, 32768) .* 0xea

write_byte(0x7ffc, nop, 0x00)
write_byte(0x7ffd, nop, 0x80)

write_byte(0x0000, nop, 0xa9)
write_byte(0x0001, nop, 0x42)

write_byte(0x0002, nop, 0x8d)
write_byte(0x0003, nop, 0x00)
write_byte(0x0004, nop, 0x70)

open("nop.bin", "w") do f
    write(f, nop)
end
