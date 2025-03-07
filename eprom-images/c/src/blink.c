#define STA(address, value) ((*(volatile unsigned char*)address) = (value))

void main()
{
	STA(0x6002, 0xFF);
	while (1)
	{
		STA(0x6000, 0xAA);
		STA(0x6000, 0x55);
	}
}
