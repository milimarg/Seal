#include "../includes/Cpu.hpp"
#include "../includes/Bus.hpp"

Cpu::Cpu()
{
	lookup = {
		{ "BRK", &Cpu::BRK, &Cpu::IMM, 7 },{ "ORA", &Cpu::ORA, &Cpu::IZX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 3 },{ "ORA", &Cpu::ORA, &Cpu::ZP0, 3 },{ "ASL", &Cpu::ASL, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "PHP", &Cpu::PHP, &Cpu::IMP, 3 },{ "ORA", &Cpu::ORA, &Cpu::IMM, 2 },{ "ASL", &Cpu::ASL, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ORA", &Cpu::ORA, &Cpu::ABS, 4 },{ "ASL", &Cpu::ASL, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "BPL", &Cpu::BPL, &Cpu::REL, 2 },{ "ORA", &Cpu::ORA, &Cpu::IZY, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ORA", &Cpu::ORA, &Cpu::ZPX, 4 },{ "ASL", &Cpu::ASL, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "CLC", &Cpu::CLC, &Cpu::IMP, 2 },{ "ORA", &Cpu::ORA, &Cpu::ABY, 4 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ORA", &Cpu::ORA, &Cpu::ABX, 4 },{ "ASL", &Cpu::ASL, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "JSR", &Cpu::JSR, &Cpu::ABS, 6 },{ "AND", &Cpu::AND, &Cpu::IZX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "BIT", &Cpu::BIT, &Cpu::ZP0, 3 },{ "AND", &Cpu::AND, &Cpu::ZP0, 3 },{ "ROL", &Cpu::ROL, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "PLP", &Cpu::PLP, &Cpu::IMP, 4 },{ "AND", &Cpu::AND, &Cpu::IMM, 2 },{ "ROL", &Cpu::ROL, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "BIT", &Cpu::BIT, &Cpu::ABS, 4 },{ "AND", &Cpu::AND, &Cpu::ABS, 4 },{ "ROL", &Cpu::ROL, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "BMI", &Cpu::BMI, &Cpu::REL, 2 },{ "AND", &Cpu::AND, &Cpu::IZY, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "AND", &Cpu::AND, &Cpu::ZPX, 4 },{ "ROL", &Cpu::ROL, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "SEC", &Cpu::SEC, &Cpu::IMP, 2 },{ "AND", &Cpu::AND, &Cpu::ABY, 4 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "AND", &Cpu::AND, &Cpu::ABX, 4 },{ "ROL", &Cpu::ROL, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "RTI", &Cpu::RTI, &Cpu::IMP, 6 },{ "EOR", &Cpu::EOR, &Cpu::IZX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 3 },{ "EOR", &Cpu::EOR, &Cpu::ZP0, 3 },{ "LSR", &Cpu::LSR, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "PHA", &Cpu::PHA, &Cpu::IMP, 3 },{ "EOR", &Cpu::EOR, &Cpu::IMM, 2 },{ "LSR", &Cpu::LSR, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "JMP", &Cpu::JMP, &Cpu::ABS, 3 },{ "EOR", &Cpu::EOR, &Cpu::ABS, 4 },{ "LSR", &Cpu::LSR, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "BVC", &Cpu::BVC, &Cpu::REL, 2 },{ "EOR", &Cpu::EOR, &Cpu::IZY, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "EOR", &Cpu::EOR, &Cpu::ZPX, 4 },{ "LSR", &Cpu::LSR, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "CLI", &Cpu::CLI, &Cpu::IMP, 2 },{ "EOR", &Cpu::EOR, &Cpu::ABY, 4 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "EOR", &Cpu::EOR, &Cpu::ABX, 4 },{ "LSR", &Cpu::LSR, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "RTS", &Cpu::RTS, &Cpu::IMP, 6 },{ "ADC", &Cpu::ADC, &Cpu::IZX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 3 },{ "ADC", &Cpu::ADC, &Cpu::ZP0, 3 },{ "ROR", &Cpu::ROR, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "PLA", &Cpu::PLA, &Cpu::IMP, 4 },{ "ADC", &Cpu::ADC, &Cpu::IMM, 2 },{ "ROR", &Cpu::ROR, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "JMP", &Cpu::JMP, &Cpu::IND, 5 },{ "ADC", &Cpu::ADC, &Cpu::ABS, 4 },{ "ROR", &Cpu::ROR, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "BVS", &Cpu::BVS, &Cpu::REL, 2 },{ "ADC", &Cpu::ADC, &Cpu::IZY, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ADC", &Cpu::ADC, &Cpu::ZPX, 4 },{ "ROR", &Cpu::ROR, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "SEI", &Cpu::SEI, &Cpu::IMP, 2 },{ "ADC", &Cpu::ADC, &Cpu::ABY, 4 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "ADC", &Cpu::ADC, &Cpu::ABX, 4 },{ "ROR", &Cpu::ROR, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "STA", &Cpu::STA, &Cpu::IZX, 6 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "STY", &Cpu::STY, &Cpu::ZP0, 3 },{ "STA", &Cpu::STA, &Cpu::ZP0, 3 },{ "STX", &Cpu::STX, &Cpu::ZP0, 3 },{ "???", &Cpu::XXX, &Cpu::IMP, 3 },{ "DEY", &Cpu::DEY, &Cpu::IMP, 2 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "TXA", &Cpu::TXA, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "STY", &Cpu::STY, &Cpu::ABS, 4 },{ "STA", &Cpu::STA, &Cpu::ABS, 4 },{ "STX", &Cpu::STX, &Cpu::ABS, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },
		{ "BCC", &Cpu::BCC, &Cpu::REL, 2 },{ "STA", &Cpu::STA, &Cpu::IZY, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "STY", &Cpu::STY, &Cpu::ZPX, 4 },{ "STA", &Cpu::STA, &Cpu::ZPX, 4 },{ "STX", &Cpu::STX, &Cpu::ZPY, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },{ "TYA", &Cpu::TYA, &Cpu::IMP, 2 },{ "STA", &Cpu::STA, &Cpu::ABY, 5 },{ "TXS", &Cpu::TXS, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "???", &Cpu::NOP, &Cpu::IMP, 5 },{ "STA", &Cpu::STA, &Cpu::ABX, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },
		{ "LDY", &Cpu::LDY, &Cpu::IMM, 2 },{ "LDA", &Cpu::LDA, &Cpu::IZX, 6 },{ "LDX", &Cpu::LDX, &Cpu::IMM, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "LDY", &Cpu::LDY, &Cpu::ZP0, 3 },{ "LDA", &Cpu::LDA, &Cpu::ZP0, 3 },{ "LDX", &Cpu::LDX, &Cpu::ZP0, 3 },{ "???", &Cpu::XXX, &Cpu::IMP, 3 },{ "TAY", &Cpu::TAY, &Cpu::IMP, 2 },{ "LDA", &Cpu::LDA, &Cpu::IMM, 2 },{ "TAX", &Cpu::TAX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "LDY", &Cpu::LDY, &Cpu::ABS, 4 },{ "LDA", &Cpu::LDA, &Cpu::ABS, 4 },{ "LDX", &Cpu::LDX, &Cpu::ABS, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },
		{ "BCS", &Cpu::BCS, &Cpu::REL, 2 },{ "LDA", &Cpu::LDA, &Cpu::IZY, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "LDY", &Cpu::LDY, &Cpu::ZPX, 4 },{ "LDA", &Cpu::LDA, &Cpu::ZPX, 4 },{ "LDX", &Cpu::LDX, &Cpu::ZPY, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },{ "CLV", &Cpu::CLV, &Cpu::IMP, 2 },{ "LDA", &Cpu::LDA, &Cpu::ABY, 4 },{ "TSX", &Cpu::TSX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },{ "LDY", &Cpu::LDY, &Cpu::ABX, 4 },{ "LDA", &Cpu::LDA, &Cpu::ABX, 4 },{ "LDX", &Cpu::LDX, &Cpu::ABY, 4 },{ "???", &Cpu::XXX, &Cpu::IMP, 4 },
		{ "CPY", &Cpu::CPY, &Cpu::IMM, 2 },{ "CMP", &Cpu::CMP, &Cpu::IZX, 6 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "CPY", &Cpu::CPY, &Cpu::ZP0, 3 },{ "CMP", &Cpu::CMP, &Cpu::ZP0, 3 },{ "DEC", &Cpu::DEC, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "INY", &Cpu::INY, &Cpu::IMP, 2 },{ "CMP", &Cpu::CMP, &Cpu::IMM, 2 },{ "DEX", &Cpu::DEX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "CPY", &Cpu::CPY, &Cpu::ABS, 4 },{ "CMP", &Cpu::CMP, &Cpu::ABS, 4 },{ "DEC", &Cpu::DEC, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "BNE", &Cpu::BNE, &Cpu::REL, 2 },{ "CMP", &Cpu::CMP, &Cpu::IZY, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "CMP", &Cpu::CMP, &Cpu::ZPX, 4 },{ "DEC", &Cpu::DEC, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "CLD", &Cpu::CLD, &Cpu::IMP, 2 },{ "CMP", &Cpu::CMP, &Cpu::ABY, 4 },{ "NOP", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "CMP", &Cpu::CMP, &Cpu::ABX, 4 },{ "DEC", &Cpu::DEC, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
		{ "CPX", &Cpu::CPX, &Cpu::IMM, 2 },{ "SBC", &Cpu::SBC, &Cpu::IZX, 6 },{ "???", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "CPX", &Cpu::CPX, &Cpu::ZP0, 3 },{ "SBC", &Cpu::SBC, &Cpu::ZP0, 3 },{ "INC", &Cpu::INC, &Cpu::ZP0, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 5 },{ "INX", &Cpu::INX, &Cpu::IMP, 2 },{ "SBC", &Cpu::SBC, &Cpu::IMM, 2 },{ "NOP", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::SBC, &Cpu::IMP, 2 },{ "CPX", &Cpu::CPX, &Cpu::ABS, 4 },{ "SBC", &Cpu::SBC, &Cpu::ABS, 4 },{ "INC", &Cpu::INC, &Cpu::ABS, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },
		{ "BEQ", &Cpu::BEQ, &Cpu::REL, 2 },{ "SBC", &Cpu::SBC, &Cpu::IZY, 5 },{ "???", &Cpu::XXX, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 8 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "SBC", &Cpu::SBC, &Cpu::ZPX, 4 },{ "INC", &Cpu::INC, &Cpu::ZPX, 6 },{ "???", &Cpu::XXX, &Cpu::IMP, 6 },{ "SED", &Cpu::SED, &Cpu::IMP, 2 },{ "SBC", &Cpu::SBC, &Cpu::ABY, 4 },{ "NOP", &Cpu::NOP, &Cpu::IMP, 2 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },{ "???", &Cpu::NOP, &Cpu::IMP, 4 },{ "SBC", &Cpu::SBC, &Cpu::ABX, 4 },{ "INC", &Cpu::INC, &Cpu::ABX, 7 },{ "???", &Cpu::XXX, &Cpu::IMP, 7 },
	};
}

Cpu::~Cpu() {}

uint8_t Cpu::read(uint16_t address)
{
	return bus->cpuRead(address, false);
}

void Cpu::write(uint16_t address, uint8_t data)
{
	bus->cpuWrite(address, data);
}

void Cpu::reset()
{
	addr_abs = 0xFFFC;
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);

	pc = (hi << 8) | lo;

	a = 0;
	x = 0;
	y = 0;
	stackPtr = 0xFD;
	status = 0x00 | U;

	addr_rel = 0x0000;
	addr_abs = 0x0000;
	fetched = 0x00;

	cycles = 8;
}

void Cpu::irq()
{
	if (getFlag(I) == 0) {
		write(0x0100 + stackPtr, (pc >> 8) & 0x00FF);
		--stackPtr;
		write(0x0100 + stackPtr, pc & 0x00FF);
		--stackPtr;
		setFlag(B, 0);
		setFlag(U, 1);
		setFlag(I, 1);
		write(0x0100 + stackPtr, status);
		--stackPtr;
		addr_abs = 0xFFFE;
		uint16_t lo = read(addr_abs + 0);
		uint16_t hi = read(addr_abs + 1);
		pc = (hi << 8) | lo;
		cycles = 7;
	}
}

void Cpu::nmi()
{
	write(0x0100 + stackPtr, (pc >> 8) & 0x00FF);
	--stackPtr;
	write(0x0100 + stackPtr, pc & 0x00FF);
	--stackPtr;
	setFlag(B, 0);
	setFlag(U, 1);
	setFlag(I, 1);
	write(0x0100 + stackPtr, status);
	--stackPtr;
	addr_abs = 0xFFFA;
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);
	pc = (hi << 8) | lo;
	cycles = 8;
}

void Cpu::clock()
{
	if (cycles == 0) {
		opcode = read(pc);
		setFlag(U, true);
		++pc;
		cycles = lookup[opcode].cycles;
		uint8_t additional_cycle1 = (this->*lookup[opcode].addrmode)();
		uint8_t additional_cycle2 = (this->*lookup[opcode].operate)();
		cycles += (additional_cycle1 & additional_cycle2);
		setFlag(U, true);
	}
	++clockCount;
	--cycles;
}

uint8_t Cpu::getFlag(FLAGS6502 f)
{
	return ((status & f) > 0);
}

void Cpu::setFlag(FLAGS6502 f, bool v)
{
    status = v ? status | f : status & ~f;
}

uint8_t Cpu::IMP()
{
	fetched = a;
	return 0;
}

uint8_t Cpu::IMM()
{
	addr_abs = pc;
    ++pc;
	return 0;
}

uint8_t Cpu::ZP0()
{
	addr_abs = read(pc);	
	++pc;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t Cpu::ZPX()
{
	addr_abs = read(pc) + x;
	++pc;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t Cpu::ZPY()
{
	addr_abs = (read(pc) + y);
	++pc;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t Cpu::REL()
{
	addr_rel = read(pc);
	++pc;
	if (addr_rel & 0x80)
		addr_rel |= 0xFF00;
	return 0;
}

uint8_t Cpu::ABS()
{
	uint16_t lo = read(pc);
	++pc;
	uint16_t hi = read(pc);
	++pc;
	addr_abs = (hi << 8) | lo;
	return 0;
}

uint8_t Cpu::ABX()
{
	uint16_t lo = read(pc);
	++pc;
	uint16_t hi = read(pc);
	++pc;
	addr_abs = (hi << 8) | lo;
	addr_abs += x;
	return (addr_abs & 0xFF00) != (hi << 8);
}

uint8_t Cpu::ABY()
{
	uint16_t lo = read(pc);
	++pc;
	uint16_t hi = read(pc);
	++pc;
	addr_abs = (hi << 8) | lo;
	addr_abs += y;
	return (addr_abs & 0xFF00) != (hi << 8);
}

uint8_t Cpu::IND()
{
	uint16_t ptr_lo = read(pc);
	++pc;
	uint16_t ptr_hi = read(pc);
	++pc;
	uint16_t ptr = (ptr_hi << 8) | ptr_lo;
	if (ptr_lo == 0x00FF) // hardware bug
		addr_abs = (read(ptr & 0xFF00) << 8) | read(ptr + 0);
	else
		addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);
	return 0;
}

uint8_t Cpu::IZX()
{
	uint16_t t = read(pc);
	++pc;
	uint16_t lo = read((uint16_t)(t + (uint16_t)x) & 0x00FF);
	uint16_t hi = read((uint16_t)(t + (uint16_t)x + 1) & 0x00FF);
	addr_abs = (hi << 8) | lo;
	return 0;
}

uint8_t Cpu::IZY()
{
	uint16_t t = read(pc);
	++pc;
	uint16_t lo = read(t & 0x00FF);
	uint16_t hi = read((t + 1) & 0x00FF);
	addr_abs = ((hi << 8) | lo) + y;
	return (addr_abs & 0xFF00) != (hi << 8);
}

uint8_t Cpu::fetch()
{
	if (!(lookup[opcode].addrmode == &Cpu::IMP))
		fetched = read(addr_abs);
	return fetched;
}

uint8_t Cpu::ADC()
{
	fetch();
	temp = (uint16_t)a + (uint16_t)fetched + (uint16_t)getFlag(C);
	setFlag(C, temp > 255);
	setFlag(Z, (temp & 0x00FF) == 0);
	setFlag(V, (~((uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^ (uint16_t)temp)) & 0x0080);
	setFlag(N, temp & 0x80);
	a = temp & 0x00FF;
	return 1;
}

uint8_t Cpu::SBC()
{
	fetch();
	uint16_t value = ((uint16_t)fetched) ^ 0x00FF;
	temp = (uint16_t)a + value + (uint16_t)getFlag(C);
	setFlag(C, temp & 0xFF00);
	setFlag(Z, ((temp & 0x00FF) == 0));
	setFlag(V, (temp ^ (uint16_t)a) & (temp ^ value) & 0x0080);
	setFlag(N, temp & 0x0080);
	a = temp & 0x00FF;
	return 1;
}

uint8_t Cpu::AND()
{
	fetch();
	a &= fetched;
	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);
	return 1;
}

uint8_t Cpu::ASL()
{
	fetch();
	temp = (uint16_t)fetched << 1;
	setFlag(C, (temp & 0xFF00) > 0);
	setFlag(Z, (temp & 0x00FF) == 0x00);
	setFlag(N, temp & 0x80);
	if (lookup[opcode].addrmode == &Cpu::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t Cpu::BCC()
{
	if (getFlag(C) != 0)
        return 0;
    ++cycles;
    addr_abs = pc + addr_rel;
    if((addr_abs & 0xFF00) != (pc & 0xFF00))
        ++cycles;
    pc = addr_abs;
	return 0;
}

uint8_t Cpu::BCS()
{
	if (getFlag(C) != 1)
        return 0;
    ++cycles;
    addr_abs = pc + addr_rel;
    if ((addr_abs & 0xFF00) != (pc & 0xFF00))
        ++cycles;
    pc = addr_abs;
	return 0;
}

uint8_t Cpu::BEQ()
{
	if (getFlag(Z) != 1)
        return 0;
    ++cycles;
    addr_abs = pc + addr_rel;
    if ((addr_abs & 0xFF00) != (pc & 0xFF00))
        ++cycles;
    pc = addr_abs;
	return 0;
}

uint8_t Cpu::BIT()
{
	fetch();
	temp = a & fetched;
	setFlag(Z, (temp & 0x00FF) == 0x00);
	setFlag(N, fetched & (1 << 7));
	setFlag(V, fetched & (1 << 6));
	return 0;
}

uint8_t Cpu::BMI()
{
	if (getFlag(N) != 1)
        return 0;
    ++cycles;
    addr_abs = pc + addr_rel;
    if ((addr_abs & 0xFF00) != (pc & 0xFF00))
        ++cycles;
    pc = addr_abs;
	return 0;
}

uint8_t Cpu::BNE()
{
	if (getFlag(Z) != 0)
        return 0;
    ++cycles;
    addr_abs = pc + addr_rel;
    if ((addr_abs & 0xFF00) != (pc & 0xFF00))
        ++cycles;
    pc = addr_abs;
	return 0;
}

uint8_t Cpu::BPL()
{
	if (getFlag(N) != 0)
        return 0;
    ++cycles;
    addr_abs = pc + addr_rel;
    if ((addr_abs & 0xFF00) != (pc & 0xFF00))
        ++cycles;
    pc = addr_abs;
	return 0;
}

uint8_t Cpu::BRK()
{
    ++pc;
	setFlag(I, 1);
	write(0x0100 + stackPtr, (pc >> 8) & 0x00FF);
    --stackPtr;
	write(0x0100 + stackPtr, pc & 0x00FF);
    --stackPtr;
	setFlag(B, 1);
	write(0x0100 + stackPtr, status);
    --stackPtr;
	setFlag(B, 0);
	pc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) << 8);
	return 0;
}

uint8_t Cpu::BVC()
{
	if (getFlag(V) != 0)
        return 0;
    ++cycles;
    addr_abs = pc + addr_rel;
    if ((addr_abs & 0xFF00) != (pc & 0xFF00))
        ++cycles;
    pc = addr_abs;
	return 0;
}

uint8_t Cpu::BVS()
{
	if (getFlag(V) != 1)
        return 0;
    ++cycles;
    addr_abs = pc + addr_rel;
    if ((addr_abs & 0xFF00) != (pc & 0xFF00))
        ++cycles;
    pc = addr_abs;
	return 0;
}

uint8_t Cpu::CLC()
{
	setFlag(C, false);
	return 0;
}

uint8_t Cpu::CLD()
{
	setFlag(D, false);
	return 0;
}

uint8_t Cpu::CLI()
{
	setFlag(I, false);
	return 0;
}

uint8_t Cpu::CLV()
{
	setFlag(V, false);
	return 0;
}

uint8_t Cpu::CMP()
{
	fetch();
	temp = (uint16_t)a - (uint16_t)fetched;
	setFlag(C, a >= fetched);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);
	return 1;
}

uint8_t Cpu::CPX()
{
	fetch();
	temp = (uint16_t)x - (uint16_t)fetched;
	setFlag(C, x >= fetched);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);
	return 0;
}

uint8_t Cpu::CPY()
{
	fetch();
	temp = (uint16_t)y - (uint16_t)fetched;
	setFlag(C, y >= fetched);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);
	return 0;
}

uint8_t Cpu::DEC()
{
	fetch();
	temp = fetched - 1;
	write(addr_abs, temp & 0x00FF);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);
	return 0;
}

uint8_t Cpu::DEX()
{
	--x;
	setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);
	return 0;
}

uint8_t Cpu::DEY()
{
	--y;
	setFlag(Z, y == 0x00);
	setFlag(N, y & 0x80);
	return 0;
}

uint8_t Cpu::EOR()
{
	fetch();
	a ^= fetched;
	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);
	return 1;
}

uint8_t Cpu::INC()
{
	fetch();
	temp = fetched + 1;
	write(addr_abs, temp & 0x00FF);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);
	return 0;
}

uint8_t Cpu::INX()
{
	++x;
	setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);
	return 0;
}

uint8_t Cpu::INY()
{
	++y;
	setFlag(Z, y == 0x00);
	setFlag(N, y & 0x80);
	return 0;
}

uint8_t Cpu::JMP()
{
	pc = addr_abs;
	return 0;
}

uint8_t Cpu::JSR()
{
	--pc;
	write(0x0100 + stackPtr, (pc >> 8) & 0x00FF);
	--stackPtr;
	write(0x0100 + stackPtr, pc & 0x00FF);
	--stackPtr;
	pc = addr_abs;
	return 0;
}

uint8_t Cpu::LDA()
{
	fetch();
	a = fetched;
	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);
	return 1;
}

uint8_t Cpu::LDX()
{
	fetch();
	x = fetched;
	setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);
	return 1;
}

uint8_t Cpu::LDY()
{
	fetch();
	y = fetched;
	setFlag(Z, y == 0x00);
	setFlag(N, y & 0x80);
	return 1;
}

uint8_t Cpu::LSR()
{
	fetch();
	setFlag(C, fetched & 0x0001);
	temp = fetched >> 1;
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);
	if (lookup[opcode].addrmode == &Cpu::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t Cpu::NOP()
{
	switch (opcode) {
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 1;
	}
	return 0;
}

uint8_t Cpu::ORA()
{
	fetch();
	a |= fetched;
	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);
	return 1;
}

uint8_t Cpu::PHA()
{
	write(0x0100 + stackPtr, a);
	--stackPtr;
	return 0;
}

uint8_t Cpu::PHP()
{
	write(0x0100 + stackPtr, status | B | U);
	setFlag(B, 0);
	setFlag(U, 0);
	--stackPtr;
	return 0;
}

uint8_t Cpu::PLA()
{
	++stackPtr;
	a = read(0x0100 + stackPtr);
	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);
	return 0;
}

uint8_t Cpu::PLP()
{
	++stackPtr;
	status = read(0x0100 + stackPtr);
	setFlag(U, 1);
	return 0;
}

uint8_t Cpu::ROL()
{
	fetch();
	temp = (uint16_t)(fetched << 1) | getFlag(C);
	setFlag(C, temp & 0xFF00);
	setFlag(Z, (temp & 0x00FF) == 0x0000);
	setFlag(N, temp & 0x0080);
	if (lookup[opcode].addrmode == &Cpu::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t Cpu::ROR()
{
	fetch();
	temp = (uint16_t)(getFlag(C) << 7) | (fetched >> 1);
	setFlag(C, fetched & 0x01);
	setFlag(Z, (temp & 0x00FF) == 0x00);
	setFlag(N, temp & 0x0080);
	if (lookup[opcode].addrmode == &Cpu::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t Cpu::RTI()
{
	++stackPtr;
	status = read(0x0100 + stackPtr);
	status &= ~B;
	status &= ~U;
	++stackPtr;
	pc = (uint16_t)read(0x0100 + stackPtr);
	++stackPtr;
	pc |= (uint16_t)read(0x0100 + stackPtr) << 8;
	return 0;
}

uint8_t Cpu::RTS()
{
	++stackPtr;
	pc = (uint16_t)read(0x0100 + stackPtr);
	++stackPtr;
	pc |= (uint16_t)read(0x0100 + stackPtr) << 8;
	++pc;
	return 0;
}

uint8_t Cpu::SEC()
{
	setFlag(C, true);
	return 0;
}

uint8_t Cpu::SED()
{
	setFlag(D, true);
	return 0;
}

uint8_t Cpu::SEI()
{
	setFlag(I, true);
	return 0;
}

uint8_t Cpu::STA()
{
	write(addr_abs, a);
	return 0;
}

uint8_t Cpu::STX()
{
	write(addr_abs, x);
	return 0;
}

uint8_t Cpu::STY()
{
	write(addr_abs, y);
	return 0;
}

uint8_t Cpu::TAX()
{
	x = a;
	setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);
	return 0;
}

uint8_t Cpu::TAY()
{
	y = a;
	setFlag(Z, y == 0x00);
	setFlag(N, y & 0x80);
	return 0;
}

uint8_t Cpu::TSX()
{
	x = stackPtr;
	setFlag(Z, x == 0x00);
	setFlag(N, x & 0x80);
	return 0;
}

uint8_t Cpu::TXA()
{
	a = x;
	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);
	return 0;
}

uint8_t Cpu::TXS()
{
	stackPtr = x;
	return 0;
}

uint8_t Cpu::TYA()
{
	a = y;
	setFlag(Z, a == 0x00);
	setFlag(N, a & 0x80);
	return 0;
}

uint8_t Cpu::XXX()
{
	return 0;
}

bool Cpu::complete()
{
	return cycles == 0;
}

void Cpu::connectBus(Bus *n)
{
    bus = n;
}

std::map<uint16_t, std::string> Cpu::disassemble(uint16_t nStart, uint16_t nStop)
{
	uint32_t address = nStart;
	uint8_t value = 0x00, lo = 0x00, hi = 0x00;
	std::map<uint16_t, std::string> mapLines;
	uint16_t line_addr = 0;
	auto hex = [](uint32_t n, uint8_t d) {
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	while (address <= (uint32_t)nStop) {
		line_addr = address;
		std::string sInst = "$" + hex(address, 4) + ": ";
		uint8_t opcode = bus->cpuRead(address, true); address++;
		sInst += lookup[opcode].name + " ";
		if (lookup[opcode].addrmode == &Cpu::IMP) {
			sInst += " {IMP}";
		} else if (lookup[opcode].addrmode == &Cpu::IMM) {
			value = bus->cpuRead(address, true); address++;
			sInst += "#$" + hex(value, 2) + " {IMM}";
		} else if (lookup[opcode].addrmode == &Cpu::ZP0) {
			lo = bus->cpuRead(address, true); address++;
			hi = 0x00;												
			sInst += "$" + hex(lo, 2) + " {ZP0}";
		} else if (lookup[opcode].addrmode == &Cpu::ZPX) {
			lo = bus->cpuRead(address, true); address++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", X {ZPX}";
		} else if (lookup[opcode].addrmode == &Cpu::ZPY) {
			lo = bus->cpuRead(address, true); address++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", Y {ZPY}";
		} else if (lookup[opcode].addrmode == &Cpu::IZX) {
			lo = bus->cpuRead(address, true); address++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + ", X) {IZX}";
		} else if (lookup[opcode].addrmode == &Cpu::IZY) {
			lo = bus->cpuRead(address, true); address++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + "), Y {IZY}";
		} else if (lookup[opcode].addrmode == &Cpu::ABS) {
			lo = bus->cpuRead(address, true); address++;
			hi = bus->cpuRead(address, true); address++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + " {ABS}";
		} else if (lookup[opcode].addrmode == &Cpu::ABX) {
			lo = bus->cpuRead(address, true); address++;
			hi = bus->cpuRead(address, true); address++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", X {ABX}";
		} else if (lookup[opcode].addrmode == &Cpu::ABY) {
			lo = bus->cpuRead(address, true); address++;
			hi = bus->cpuRead(address, true); address++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", Y {ABY}";
		} else if (lookup[opcode].addrmode == &Cpu::IND) {
			lo = bus->cpuRead(address, true); address++;
			hi = bus->cpuRead(address, true); address++;
			sInst += "($" + hex((uint16_t)(hi << 8) | lo, 4) + ") {IND}";
		} else if (lookup[opcode].addrmode == &Cpu::REL) {
			value = bus->cpuRead(address, true); address++;
			sInst += "$" + hex(value, 2) + " [$" + hex(address + (int8_t)value, 4) + "] {REL}";
		}
		mapLines[line_addr] = sInst;
	}
	return mapLines;
}
