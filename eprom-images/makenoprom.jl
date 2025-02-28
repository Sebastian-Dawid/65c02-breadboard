function write_byte(addr, rom, byte)
    rom[addr + 1] = byte
end

code_addr = 0x0000

function write_instruction(rom, bytes)
    for i in eachindex(bytes)
        write_byte(code_addr, rom, bytes[i])
        global code_addr += 1
    end
end

nop = ones(UInt8, 32768) .* 0xea

write_instruction(nop, [0xa9, 0xff])
write_instruction(nop, [0x8d, 0x02, 0x60])

write_instruction(nop, [0xa9, 0x42])
write_instruction(nop, [0x8d, 0x00, 0x60])

write_instruction(nop, [0xa9, 0xaa])
write_instruction(nop, [0x8d, 0x00, 0x60])

write_instruction(nop, [0x4c, 0x05, 0x80])

write_byte(0x7ffc, nop, 0x00)
write_byte(0x7ffd, nop, 0x80)

open("nop.bin", "w") do f
    write(f, nop)
end
