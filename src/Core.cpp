#include "../includes/Core.hpp"
#include "../includes/Bus.hpp"

Core::Core()
{
	lookup = {
		{ "BRK", &Core::BRK, &Core::IMM, 7 },{ "ORA", &Core::ORA, &Core::IZX, 6 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 8 },{ "???", &Core::NOP, &Core::IMP, 3 },{ "ORA", &Core::ORA, &Core::ZP0, 3 },{ "ASL", &Core::ASL, &Core::ZP0, 5 },{ "???", &Core::XXX, &Core::IMP, 5 },{ "PHP", &Core::PHP, &Core::IMP, 3 },{ "ORA", &Core::ORA, &Core::IMM, 2 },{ "ASL", &Core::ASL, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "???", &Core::NOP, &Core::IMP, 4 },{ "ORA", &Core::ORA, &Core::ABS, 4 },{ "ASL", &Core::ASL, &Core::ABS, 6 },{ "???", &Core::XXX, &Core::IMP, 6 },
		{ "BPL", &Core::BPL, &Core::REL, 2 },{ "ORA", &Core::ORA, &Core::IZY, 5 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 8 },{ "???", &Core::NOP, &Core::IMP, 4 },{ "ORA", &Core::ORA, &Core::ZPX, 4 },{ "ASL", &Core::ASL, &Core::ZPX, 6 },{ "???", &Core::XXX, &Core::IMP, 6 },{ "CLC", &Core::CLC, &Core::IMP, 2 },{ "ORA", &Core::ORA, &Core::ABY, 4 },{ "???", &Core::NOP, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 7 },{ "???", &Core::NOP, &Core::IMP, 4 },{ "ORA", &Core::ORA, &Core::ABX, 4 },{ "ASL", &Core::ASL, &Core::ABX, 7 },{ "???", &Core::XXX, &Core::IMP, 7 },
		{ "JSR", &Core::JSR, &Core::ABS, 6 },{ "AND", &Core::AND, &Core::IZX, 6 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 8 },{ "BIT", &Core::BIT, &Core::ZP0, 3 },{ "AND", &Core::AND, &Core::ZP0, 3 },{ "ROL", &Core::ROL, &Core::ZP0, 5 },{ "???", &Core::XXX, &Core::IMP, 5 },{ "PLP", &Core::PLP, &Core::IMP, 4 },{ "AND", &Core::AND, &Core::IMM, 2 },{ "ROL", &Core::ROL, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "BIT", &Core::BIT, &Core::ABS, 4 },{ "AND", &Core::AND, &Core::ABS, 4 },{ "ROL", &Core::ROL, &Core::ABS, 6 },{ "???", &Core::XXX, &Core::IMP, 6 },
		{ "BMI", &Core::BMI, &Core::REL, 2 },{ "AND", &Core::AND, &Core::IZY, 5 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 8 },{ "???", &Core::NOP, &Core::IMP, 4 },{ "AND", &Core::AND, &Core::ZPX, 4 },{ "ROL", &Core::ROL, &Core::ZPX, 6 },{ "???", &Core::XXX, &Core::IMP, 6 },{ "SEC", &Core::SEC, &Core::IMP, 2 },{ "AND", &Core::AND, &Core::ABY, 4 },{ "???", &Core::NOP, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 7 },{ "???", &Core::NOP, &Core::IMP, 4 },{ "AND", &Core::AND, &Core::ABX, 4 },{ "ROL", &Core::ROL, &Core::ABX, 7 },{ "???", &Core::XXX, &Core::IMP, 7 },
		{ "RTI", &Core::RTI, &Core::IMP, 6 },{ "EOR", &Core::EOR, &Core::IZX, 6 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 8 },{ "???", &Core::NOP, &Core::IMP, 3 },{ "EOR", &Core::EOR, &Core::ZP0, 3 },{ "LSR", &Core::LSR, &Core::ZP0, 5 },{ "???", &Core::XXX, &Core::IMP, 5 },{ "PHA", &Core::PHA, &Core::IMP, 3 },{ "EOR", &Core::EOR, &Core::IMM, 2 },{ "LSR", &Core::LSR, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "JMP", &Core::JMP, &Core::ABS, 3 },{ "EOR", &Core::EOR, &Core::ABS, 4 },{ "LSR", &Core::LSR, &Core::ABS, 6 },{ "???", &Core::XXX, &Core::IMP, 6 },
		{ "BVC", &Core::BVC, &Core::REL, 2 },{ "EOR", &Core::EOR, &Core::IZY, 5 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 8 },{ "???", &Core::NOP, &Core::IMP, 4 },{ "EOR", &Core::EOR, &Core::ZPX, 4 },{ "LSR", &Core::LSR, &Core::ZPX, 6 },{ "???", &Core::XXX, &Core::IMP, 6 },{ "CLI", &Core::CLI, &Core::IMP, 2 },{ "EOR", &Core::EOR, &Core::ABY, 4 },{ "???", &Core::NOP, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 7 },{ "???", &Core::NOP, &Core::IMP, 4 },{ "EOR", &Core::EOR, &Core::ABX, 4 },{ "LSR", &Core::LSR, &Core::ABX, 7 },{ "???", &Core::XXX, &Core::IMP, 7 },
		{ "RTS", &Core::RTS, &Core::IMP, 6 },{ "ADC", &Core::ADC, &Core::IZX, 6 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 8 },{ "???", &Core::NOP, &Core::IMP, 3 },{ "ADC", &Core::ADC, &Core::ZP0, 3 },{ "ROR", &Core::ROR, &Core::ZP0, 5 },{ "???", &Core::XXX, &Core::IMP, 5 },{ "PLA", &Core::PLA, &Core::IMP, 4 },{ "ADC", &Core::ADC, &Core::IMM, 2 },{ "ROR", &Core::ROR, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "JMP", &Core::JMP, &Core::IND, 5 },{ "ADC", &Core::ADC, &Core::ABS, 4 },{ "ROR", &Core::ROR, &Core::ABS, 6 },{ "???", &Core::XXX, &Core::IMP, 6 },
		{ "BVS", &Core::BVS, &Core::REL, 2 },{ "ADC", &Core::ADC, &Core::IZY, 5 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 8 },{ "???", &Core::NOP, &Core::IMP, 4 },{ "ADC", &Core::ADC, &Core::ZPX, 4 },{ "ROR", &Core::ROR, &Core::ZPX, 6 },{ "???", &Core::XXX, &Core::IMP, 6 },{ "SEI", &Core::SEI, &Core::IMP, 2 },{ "ADC", &Core::ADC, &Core::ABY, 4 },{ "???", &Core::NOP, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 7 },{ "???", &Core::NOP, &Core::IMP, 4 },{ "ADC", &Core::ADC, &Core::ABX, 4 },{ "ROR", &Core::ROR, &Core::ABX, 7 },{ "???", &Core::XXX, &Core::IMP, 7 },
		{ "???", &Core::NOP, &Core::IMP, 2 },{ "STA", &Core::STA, &Core::IZX, 6 },{ "???", &Core::NOP, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 6 },{ "STY", &Core::STY, &Core::ZP0, 3 },{ "STA", &Core::STA, &Core::ZP0, 3 },{ "STX", &Core::STX, &Core::ZP0, 3 },{ "???", &Core::XXX, &Core::IMP, 3 },{ "DEY", &Core::DEY, &Core::IMP, 2 },{ "???", &Core::NOP, &Core::IMP, 2 },{ "TXA", &Core::TXA, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "STY", &Core::STY, &Core::ABS, 4 },{ "STA", &Core::STA, &Core::ABS, 4 },{ "STX", &Core::STX, &Core::ABS, 4 },{ "???", &Core::XXX, &Core::IMP, 4 },
		{ "BCC", &Core::BCC, &Core::REL, 2 },{ "STA", &Core::STA, &Core::IZY, 6 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 6 },{ "STY", &Core::STY, &Core::ZPX, 4 },{ "STA", &Core::STA, &Core::ZPX, 4 },{ "STX", &Core::STX, &Core::ZPY, 4 },{ "???", &Core::XXX, &Core::IMP, 4 },{ "TYA", &Core::TYA, &Core::IMP, 2 },{ "STA", &Core::STA, &Core::ABY, 5 },{ "TXS", &Core::TXS, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 5 },{ "???", &Core::NOP, &Core::IMP, 5 },{ "STA", &Core::STA, &Core::ABX, 5 },{ "???", &Core::XXX, &Core::IMP, 5 },{ "???", &Core::XXX, &Core::IMP, 5 },
		{ "LDY", &Core::LDY, &Core::IMM, 2 },{ "LDA", &Core::LDA, &Core::IZX, 6 },{ "LDX", &Core::LDX, &Core::IMM, 2 },{ "???", &Core::XXX, &Core::IMP, 6 },{ "LDY", &Core::LDY, &Core::ZP0, 3 },{ "LDA", &Core::LDA, &Core::ZP0, 3 },{ "LDX", &Core::LDX, &Core::ZP0, 3 },{ "???", &Core::XXX, &Core::IMP, 3 },{ "TAY", &Core::TAY, &Core::IMP, 2 },{ "LDA", &Core::LDA, &Core::IMM, 2 },{ "TAX", &Core::TAX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "LDY", &Core::LDY, &Core::ABS, 4 },{ "LDA", &Core::LDA, &Core::ABS, 4 },{ "LDX", &Core::LDX, &Core::ABS, 4 },{ "???", &Core::XXX, &Core::IMP, 4 },
		{ "BCS", &Core::BCS, &Core::REL, 2 },{ "LDA", &Core::LDA, &Core::IZY, 5 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 5 },{ "LDY", &Core::LDY, &Core::ZPX, 4 },{ "LDA", &Core::LDA, &Core::ZPX, 4 },{ "LDX", &Core::LDX, &Core::ZPY, 4 },{ "???", &Core::XXX, &Core::IMP, 4 },{ "CLV", &Core::CLV, &Core::IMP, 2 },{ "LDA", &Core::LDA, &Core::ABY, 4 },{ "TSX", &Core::TSX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 4 },{ "LDY", &Core::LDY, &Core::ABX, 4 },{ "LDA", &Core::LDA, &Core::ABX, 4 },{ "LDX", &Core::LDX, &Core::ABY, 4 },{ "???", &Core::XXX, &Core::IMP, 4 },
		{ "CPY", &Core::CPY, &Core::IMM, 2 },{ "CMP", &Core::CMP, &Core::IZX, 6 },{ "???", &Core::NOP, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 8 },{ "CPY", &Core::CPY, &Core::ZP0, 3 },{ "CMP", &Core::CMP, &Core::ZP0, 3 },{ "DEC", &Core::DEC, &Core::ZP0, 5 },{ "???", &Core::XXX, &Core::IMP, 5 },{ "INY", &Core::INY, &Core::IMP, 2 },{ "CMP", &Core::CMP, &Core::IMM, 2 },{ "DEX", &Core::DEX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "CPY", &Core::CPY, &Core::ABS, 4 },{ "CMP", &Core::CMP, &Core::ABS, 4 },{ "DEC", &Core::DEC, &Core::ABS, 6 },{ "???", &Core::XXX, &Core::IMP, 6 },
		{ "BNE", &Core::BNE, &Core::REL, 2 },{ "CMP", &Core::CMP, &Core::IZY, 5 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 8 },{ "???", &Core::NOP, &Core::IMP, 4 },{ "CMP", &Core::CMP, &Core::ZPX, 4 },{ "DEC", &Core::DEC, &Core::ZPX, 6 },{ "???", &Core::XXX, &Core::IMP, 6 },{ "CLD", &Core::CLD, &Core::IMP, 2 },{ "CMP", &Core::CMP, &Core::ABY, 4 },{ "NOP", &Core::NOP, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 7 },{ "???", &Core::NOP, &Core::IMP, 4 },{ "CMP", &Core::CMP, &Core::ABX, 4 },{ "DEC", &Core::DEC, &Core::ABX, 7 },{ "???", &Core::XXX, &Core::IMP, 7 },
		{ "CPX", &Core::CPX, &Core::IMM, 2 },{ "SBC", &Core::SBC, &Core::IZX, 6 },{ "???", &Core::NOP, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 8 },{ "CPX", &Core::CPX, &Core::ZP0, 3 },{ "SBC", &Core::SBC, &Core::ZP0, 3 },{ "INC", &Core::INC, &Core::ZP0, 5 },{ "???", &Core::XXX, &Core::IMP, 5 },{ "INX", &Core::INX, &Core::IMP, 2 },{ "SBC", &Core::SBC, &Core::IMM, 2 },{ "NOP", &Core::NOP, &Core::IMP, 2 },{ "???", &Core::SBC, &Core::IMP, 2 },{ "CPX", &Core::CPX, &Core::ABS, 4 },{ "SBC", &Core::SBC, &Core::ABS, 4 },{ "INC", &Core::INC, &Core::ABS, 6 },{ "???", &Core::XXX, &Core::IMP, 6 },
		{ "BEQ", &Core::BEQ, &Core::REL, 2 },{ "SBC", &Core::SBC, &Core::IZY, 5 },{ "???", &Core::XXX, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 8 },{ "???", &Core::NOP, &Core::IMP, 4 },{ "SBC", &Core::SBC, &Core::ZPX, 4 },{ "INC", &Core::INC, &Core::ZPX, 6 },{ "???", &Core::XXX, &Core::IMP, 6 },{ "SED", &Core::SED, &Core::IMP, 2 },{ "SBC", &Core::SBC, &Core::ABY, 4 },{ "NOP", &Core::NOP, &Core::IMP, 2 },{ "???", &Core::XXX, &Core::IMP, 7 },{ "???", &Core::NOP, &Core::IMP, 4 },{ "SBC", &Core::SBC, &Core::ABX, 4 },{ "INC", &Core::INC, &Core::ABX, 7 },{ "???", &Core::XXX, &Core::IMP, 7 },
	};
}

Core::~Core() {}

uint8_t Core::read(uint16_t a)
{
	return bus->cpuRead(a, false);
}

void Core::write(uint16_t a, uint8_t d)
{
	bus->cpuWrite(a, d);
}

void Core::reset()
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

void Core::irq()
{
	if (GetFlag(I) == 0)
	{
		write(0x0100 + stackPtr, (pc >> 8) & 0x00FF);
		stackPtr--;
		write(0x0100 + stackPtr, pc & 0x00FF);
		stackPtr--;

		SetFlag(B, 0);
		SetFlag(U, 1);
		SetFlag(I, 1);
		write(0x0100 + stackPtr, status);
		stackPtr--;

		addr_abs = 0xFFFE;
		uint16_t lo = read(addr_abs + 0);
		uint16_t hi = read(addr_abs + 1);
		pc = (hi << 8) | lo;

		cycles = 7;
	}
}

void Core::nmi()
{
	write(0x0100 + stackPtr, (pc >> 8) & 0x00FF);
	stackPtr--;
	write(0x0100 + stackPtr, pc & 0x00FF);
	stackPtr--;

	SetFlag(B, 0);
	SetFlag(U, 1);
	SetFlag(I, 1);
	write(0x0100 + stackPtr, status);
	stackPtr--;

	addr_abs = 0xFFFA;
	uint16_t lo = read(addr_abs + 0);
	uint16_t hi = read(addr_abs + 1);
	pc = (hi << 8) | lo;

	cycles = 8;
}

void Core::clock()
{
	if (cycles == 0)
	{
		opcode = read(pc);
		
		SetFlag(U, true);
		
		pc++;

		cycles = lookup[opcode].cycles;

		uint8_t additional_cycle1 = (this->*lookup[opcode].addrmode)();

		uint8_t additional_cycle2 = (this->*lookup[opcode].operate)();

		cycles += (additional_cycle1 & additional_cycle2);

		SetFlag(U, true);
	}
	clockCount++;
	cycles--;
}

uint8_t Core::GetFlag(FLAGS6502 f)
{
	return ((status & f) > 0) ? 1 : 0;
}

void Core::SetFlag(FLAGS6502 f, bool v)
{
	if (v)
		status |= f;
	else
		status &= ~f;
}

uint8_t Core::IMP()
{
	fetched = a;
	return 0;
}

uint8_t Core::IMM()
{
	addr_abs = pc++;	
	return 0;
}

uint8_t Core::ZP0()
{
	addr_abs = read(pc);	
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t Core::ZPX()
{
	addr_abs = (read(pc) + x);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t Core::ZPY()
{
	addr_abs = (read(pc) + y);
	pc++;
	addr_abs &= 0x00FF;
	return 0;
}

uint8_t Core::REL()
{
	addr_rel = read(pc);
	pc++;
	if (addr_rel & 0x80)
		addr_rel |= 0xFF00;
	return 0;
}

uint8_t Core::ABS()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;

	return 0;
}

uint8_t Core::ABX()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += x;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

uint8_t Core::ABY()
{
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

uint8_t Core::IND()
{
	uint16_t ptr_lo = read(pc);
	pc++;
	uint16_t ptr_hi = read(pc);
	pc++;

	uint16_t ptr = (ptr_hi << 8) | ptr_lo;

	if (ptr_lo == 0x00FF) // Simulate page boundary hardware bug
	{
		addr_abs = (read(ptr & 0xFF00) << 8) | read(ptr + 0);
	}
	else // Behave normally
	{
		addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);
	}
	return 0;
}

uint8_t Core::IZX()
{
	uint16_t t = read(pc);
	pc++;

	uint16_t lo = read((uint16_t)(t + (uint16_t)x) & 0x00FF);
	uint16_t hi = read((uint16_t)(t + (uint16_t)x + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
	
	return 0;
}

uint8_t Core::IZY()
{
	uint16_t t = read(pc);
	pc++;

	uint16_t lo = read(t & 0x00FF);
	uint16_t hi = read((t + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
	addr_abs += y;
	
	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

uint8_t Core::fetch()
{
	if (!(lookup[opcode].addrmode == &Core::IMP))
		fetched = read(addr_abs);
	return fetched;
}

uint8_t Core::ADC()
{
	// Grab the data that we are adding to the accumulator
	fetch();
	
	// Add is performed in 16-bit domain for emulation to capture any
	// carry bit, which will exist in bit 8 of the 16-bit word
	temp = (uint16_t)a + (uint16_t)fetched + (uint16_t)GetFlag(C);
	
	// The carry flag out exists in the high byte bit 0
	SetFlag(C, temp > 255);
	
	// The Zero flag is set if the result is 0
	SetFlag(Z, (temp & 0x00FF) == 0);
	
	// The signed Overflow flag is set based on all that up there! :D
	SetFlag(V, (~((uint16_t)a ^ (uint16_t)fetched) & ((uint16_t)a ^ (uint16_t)temp)) & 0x0080);
	
	// The negative flag is set to the most significant bit of the result
	SetFlag(N, temp & 0x80);
	
	// Load the result into the accumulator (it's 8-bit dont forget!)
	a = temp & 0x00FF;
	
	// This instruction has the potential to require an additional clock cycle
	return 1;
}

uint8_t Core::SBC()
{
	fetch();
	
	// Operating in 16-bit domain to capture carry out
	
	// We can invert the bottom 8 bits with bitwise xor
	uint16_t value = ((uint16_t)fetched) ^ 0x00FF;
	
	// Notice this is exactly the same as addition from here!
	temp = (uint16_t)a + value + (uint16_t)GetFlag(C);
	SetFlag(C, temp & 0xFF00);
	SetFlag(Z, ((temp & 0x00FF) == 0));
	SetFlag(V, (temp ^ (uint16_t)a) & (temp ^ value) & 0x0080);
	SetFlag(N, temp & 0x0080);
	a = temp & 0x00FF;
	return 1;
}

uint8_t Core::AND()
{
	fetch();
	a = a & fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}

uint8_t Core::ASL()
{
	fetch();
	temp = (uint16_t)fetched << 1;
	SetFlag(C, (temp & 0xFF00) > 0);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x80);
	if (lookup[opcode].addrmode == &Core::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t Core::BCC()
{
	if (GetFlag(C) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;
		
		if((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;
		
		pc = addr_abs;
	}
	return 0;
}

uint8_t Core::BCS()
{
	if (GetFlag(C) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t Core::BEQ()
{
	if (GetFlag(Z) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t Core::BIT()
{
	fetch();
	temp = a & fetched;
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, fetched & (1 << 7));
	SetFlag(V, fetched & (1 << 6));
	return 0;
}

uint8_t Core::BMI()
{
	if (GetFlag(N) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t Core::BNE()
{
	if (GetFlag(Z) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t Core::BPL()
{
	if (GetFlag(N) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t Core::BRK()
{
	pc++;
	
	SetFlag(I, 1);
	write(0x0100 + stackPtr, (pc >> 8) & 0x00FF);
	stackPtr--;
	write(0x0100 + stackPtr, pc & 0x00FF);
	stackPtr--;

	SetFlag(B, 1);
	write(0x0100 + stackPtr, status);
	stackPtr--;
	SetFlag(B, 0);

	pc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) << 8);
	return 0;
}

uint8_t Core::BVC()
{
	if (GetFlag(V) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t Core::BVS()
{
	if (GetFlag(V) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
	return 0;
}

uint8_t Core::CLC()
{
	SetFlag(C, false);
	return 0;
}

uint8_t Core::CLD()
{
	SetFlag(D, false);
	return 0;
}

uint8_t Core::CLI()
{
	SetFlag(I, false);
	return 0;
}

uint8_t Core::CLV()
{
	SetFlag(V, false);
	return 0;
}

uint8_t Core::CMP()
{
	fetch();
	temp = (uint16_t)a - (uint16_t)fetched;
	SetFlag(C, a >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 1;
}

uint8_t Core::CPX()
{
	fetch();
	temp = (uint16_t)x - (uint16_t)fetched;
	SetFlag(C, x >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 0;
}

uint8_t Core::CPY()
{
	fetch();
	temp = (uint16_t)y - (uint16_t)fetched;
	SetFlag(C, y >= fetched);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 0;
}

uint8_t Core::DEC()
{
	fetch();
	temp = fetched - 1;
	write(addr_abs, temp & 0x00FF);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 0;
}

uint8_t Core::DEX()
{
	x--;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}

uint8_t Core::DEY()
{
	y--;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 0;
}

uint8_t Core::EOR()
{
	fetch();
	a = a ^ fetched;	
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}

uint8_t Core::INC()
{
	fetch();
	temp = fetched + 1;
	write(addr_abs, temp & 0x00FF);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	return 0;
}

uint8_t Core::INX()
{
	x++;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}

uint8_t Core::INY()
{
	y++;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 0;
}

uint8_t Core::JMP()
{
	pc = addr_abs;
	return 0;
}

uint8_t Core::JSR()
{
	pc--;

	write(0x0100 + stackPtr, (pc >> 8) & 0x00FF);
	stackPtr--;
	write(0x0100 + stackPtr, pc & 0x00FF);
	stackPtr--;

	pc = addr_abs;
	return 0;
}

uint8_t Core::LDA()
{
	fetch();
	a = fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}

uint8_t Core::LDX()
{
	fetch();
	x = fetched;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 1;
}

uint8_t Core::LDY()
{
	fetch();
	y = fetched;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 1;
}

uint8_t Core::LSR()
{
	fetch();
	SetFlag(C, fetched & 0x0001);
	temp = fetched >> 1;	
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	if (lookup[opcode].addrmode == &Core::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t Core::NOP()
{
	switch (opcode) {
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 1;
		break;
	}
	return 0;
}

uint8_t Core::ORA()
{
	fetch();
	a = a | fetched;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 1;
}

uint8_t Core::PHA()
{
	write(0x0100 + stackPtr, a);
	stackPtr--;
	return 0;
}

uint8_t Core::PHP()
{
	write(0x0100 + stackPtr, status | B | U);
	SetFlag(B, 0);
	SetFlag(U, 0);
	stackPtr--;
	return 0;
}

uint8_t Core::PLA()
{
	stackPtr++;
	a = read(0x0100 + stackPtr);
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}

uint8_t Core::PLP()
{
	stackPtr++;
	status = read(0x0100 + stackPtr);
	SetFlag(U, 1);
	return 0;
}

uint8_t Core::ROL()
{
	fetch();
	temp = (uint16_t)(fetched << 1) | GetFlag(C);
	SetFlag(C, temp & 0xFF00);
	SetFlag(Z, (temp & 0x00FF) == 0x0000);
	SetFlag(N, temp & 0x0080);
	if (lookup[opcode].addrmode == &Core::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t Core::ROR()
{
	fetch();
	temp = (uint16_t)(GetFlag(C) << 7) | (fetched >> 1);
	SetFlag(C, fetched & 0x01);
	SetFlag(Z, (temp & 0x00FF) == 0x00);
	SetFlag(N, temp & 0x0080);
	if (lookup[opcode].addrmode == &Core::IMP)
		a = temp & 0x00FF;
	else
		write(addr_abs, temp & 0x00FF);
	return 0;
}

uint8_t Core::RTI()
{
	stackPtr++;
	status = read(0x0100 + stackPtr);
	status &= ~B;
	status &= ~U;

	stackPtr++;
	pc = (uint16_t)read(0x0100 + stackPtr);
	stackPtr++;
	pc |= (uint16_t)read(0x0100 + stackPtr) << 8;
	return 0;
}

uint8_t Core::RTS()
{
	stackPtr++;
	pc = (uint16_t)read(0x0100 + stackPtr);
	stackPtr++;
	pc |= (uint16_t)read(0x0100 + stackPtr) << 8;
	
	pc++;
	return 0;
}

uint8_t Core::SEC()
{
	SetFlag(C, true);
	return 0;
}

uint8_t Core::SED()
{
	SetFlag(D, true);
	return 0;
}

uint8_t Core::SEI()
{
	SetFlag(I, true);
	return 0;
}

uint8_t Core::STA()
{
	write(addr_abs, a);
	return 0;
}

uint8_t Core::STX()
{
	write(addr_abs, x);
	return 0;
}

uint8_t Core::STY()
{
	write(addr_abs, y);
	return 0;
}

uint8_t Core::TAX()
{
	x = a;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}

uint8_t Core::TAY()
{
	y = a;
	SetFlag(Z, y == 0x00);
	SetFlag(N, y & 0x80);
	return 0;
}

uint8_t Core::TSX()
{
	x = stackPtr;
	SetFlag(Z, x == 0x00);
	SetFlag(N, x & 0x80);
	return 0;
}

uint8_t Core::TXA()
{
	a = x;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}

uint8_t Core::TXS()
{
	stackPtr = x;
	return 0;
}

uint8_t Core::TYA()
{
	a = y;
	SetFlag(Z, a == 0x00);
	SetFlag(N, a & 0x80);
	return 0;
}

uint8_t Core::XXX()
{
	return 0;
}

bool Core::complete()
{
	return cycles == 0;
}

std::map<uint16_t, std::string> Core::disassemble(uint16_t nStart, uint16_t nStop)
{
	uint32_t addr = nStart;
	uint8_t value = 0x00, lo = 0x00, hi = 0x00;
	std::map<uint16_t, std::string> mapLines;
	uint16_t line_addr = 0;

	auto hex = [](uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	while (addr <= (uint32_t)nStop)
	{
		line_addr = addr;

		std::string sInst = "$" + hex(addr, 4) + ": ";

		uint8_t opcode = bus->cpuRead(addr, true); addr++;
		sInst += lookup[opcode].name + " ";

		if (lookup[opcode].addrmode == &Core::IMP)
		{
			sInst += " {IMP}";
		}
		else if (lookup[opcode].addrmode == &Core::IMM)
		{
			value = bus->cpuRead(addr, true); addr++;
			sInst += "#$" + hex(value, 2) + " {IMM}";
		}
		else if (lookup[opcode].addrmode == &Core::ZP0)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;												
			sInst += "$" + hex(lo, 2) + " {ZP0}";
		}
		else if (lookup[opcode].addrmode == &Core::ZPX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", X {ZPX}";
		}
		else if (lookup[opcode].addrmode == &Core::ZPY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;														
			sInst += "$" + hex(lo, 2) + ", Y {ZPY}";
		}
		else if (lookup[opcode].addrmode == &Core::IZX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + ", X) {IZX}";
		}
		else if (lookup[opcode].addrmode == &Core::IZY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = 0x00;								
			sInst += "($" + hex(lo, 2) + "), Y {IZY}";
		}
		else if (lookup[opcode].addrmode == &Core::ABS)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + " {ABS}";
		}
		else if (lookup[opcode].addrmode == &Core::ABX)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", X {ABX}";
		}
		else if (lookup[opcode].addrmode == &Core::ABY)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex((uint16_t)(hi << 8) | lo, 4) + ", Y {ABY}";
		}
		else if (lookup[opcode].addrmode == &Core::IND)
		{
			lo = bus->cpuRead(addr, true); addr++;
			hi = bus->cpuRead(addr, true); addr++;
			sInst += "($" + hex((uint16_t)(hi << 8) | lo, 4) + ") {IND}";
		}
		else if (lookup[opcode].addrmode == &Core::REL)
		{
			value = bus->cpuRead(addr, true); addr++;
			sInst += "$" + hex(value, 2) + " [$" + hex(addr + (int8_t)value, 4) + "] {REL}";
		}

		mapLines[line_addr] = sInst;
	}

	return mapLines;
}
