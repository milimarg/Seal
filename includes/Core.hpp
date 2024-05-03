#ifndef SEAL_CORE_HPP
    #define SEAL_CORE_HPP

class Bus;

class Core {
public:
    enum FLAGS6502 {
        C = (1 << 0), // Carry Bit
        Z = (1 << 1), // Zero
        I = (1 << 2), // Disable Interrupts
        D = (1 << 3), // Decimal Mode (unused in this implementation)
        B = (1 << 4), // Break
        U = (1 << 5), // Unused
        V = (1 << 6), // Overflow
        N = (1 << 7)  // Negative
    };

    uint8_t a = 0x00;        // Accumulator Register
    uint8_t x = 0x00;        // X Register
    uint8_t y = 0x00;        // Y Register
    uint8_t stackPtr = 0x00; // Stack Pointer (point to the location in the bus)
    uint8_t pc = 0x00;       // Program Counter
    uint8_t status = 0x00;   // Status Register

    Core();
    ~Core();

    void connectBus(Bus *n);

    // Docs: https://github.com/OneLoneCoder/olcNES/blob/master/Part%232%20-%20CPU/olc6502.cpp
    // Addressing modes
    uint8_t IMP(); // Implied
    uint8_t IMM(); // Immediate
    uint8_t ZP0(); // Zero Page
    uint8_t ZPX(); // Zero Page with X register offset
    uint8_t ZPY(); // Zero Page with Y register offset
    uint8_t REL(); // Relative
    uint8_t ABS(); // Absolute
    uint8_t ABX(); // Absolute with X register offset
    uint8_t ABY(); // Absolute with Y register offset
    uint8_t IND(); // Indirect
    uint8_t IZX(); // Indirect with X register offset
    uint8_t IZY(); // Indirect with Y register offset

    // Op Codes
    uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
    uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
    uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
    uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
    uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
    uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
    uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
    uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
    uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
    uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
    uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
    uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
    uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
    uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

    uint8_t XXX();

    void clock();
    void reset();
    void irq(); // Interrupt Request Signal
    void nmi(); // Non Maskable Interrupt Request Signal

    uint8_t fetch();
    uint8_t fetched = 0x00;

    uint16_t addr_abs = 0x0000;
    uint16_t addr_rel = 0x0000;
    uint8_t opcode = 0x00;
    uint8_t cycle = 0;

private:
    Bus *bus = nullptr;
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr);

    uint8_t getFlag(FLAGS6502 flag);
    void setFlag(FLAGS6502 flag, bool v);

    struct INSTRUCTION {
        std::string name;
        uint8_t (Core::*operate)(void) = nullptr;
        uint8_t (Core::*addrmode)(void) = nullptr;
        uint8_t cycles = 0;
    };

    std::vector<INSTRUCTION> lookup;
};

#endif //SEAL_CORE_HPP
