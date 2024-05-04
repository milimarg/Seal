#ifndef SEAL_CORE_HPP
    #define SEAL_CORE_HPP
    #include <map>
    #include <vector>
    #include <string>

    #define BASE_STACK_PTR 0x0100
    #define BYTE_CONCAT(h, l) (h << 8) | l

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

    uint8_t a = 0x00;            // Accumulator Register
    uint8_t x = 0x00;            // X Register
    uint8_t y = 0x00;            // Y Register
    uint8_t stackPtr = 0x00;     // Stack Pointer (point to the location in the bus)
    uint16_t pc = 0x0000;        // Program Counter
    uint8_t status = 0x00;       // Status Register

    Core();
    ~Core();

    void connectBus(Bus *n);

    void clock();
    void reset();
    void irq(); // Interrupt Request Signal
    void nmi(); // Non Maskable Interrupt Request Signal

    // Docs: https://github.com/OneLoneCoder/olcNES/blob/master/Part%232%20-%20CPU/Core.cpp
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
    uint8_t ADC();
    uint8_t AND(); // And (+)
    uint8_t ASL();
    uint8_t BCC(); // Branching Carry Clear
    uint8_t BCS(); // Branching
    uint8_t BEQ(); // Branching if Equal
    uint8_t BIT();
    uint8_t BMI(); // Branch if Negative
    uint8_t BNE(); // Branch if Not Equal
    uint8_t BPL(); // Branch if Positive
    uint8_t BRK(); // Break
    uint8_t BVC(); // Branch if Overflow Clear
    uint8_t BVS(); // Branch if Overflow Set
    uint8_t CLC(); // Clear Carry Flag
    uint8_t CLD(); // Clear Decimal Flag
    uint8_t CLI(); // Disable Interrupts / Clear Interrupt Flag
    uint8_t CLV(); // Clear Overflow Flag
    uint8_t CMP(); // Compare Accumulator
    uint8_t CPX(); // Compare X Register
    uint8_t CPY(); // Compare Y Register
    uint8_t DEC(); // Decrement Value at Memory Location
    uint8_t DEX(); // Decrement X Register
    uint8_t DEY(); // Decrement Y Register
    uint8_t EOR(); // Bitwise Logic XOR
    uint8_t INC(); // Increment Value at Memory Location
    uint8_t INX(); // Increment X Register
    uint8_t INY(); // Increment Y Register
    uint8_t JMP(); // Jump To Location
    uint8_t JSR(); // Jump To Sub-Routine
    uint8_t LDA(); // Load The Accumulator
    uint8_t LDX(); // Load The X Register
    uint8_t LDY(); // Load The Y Register
    uint8_t LSR();
    uint8_t NOP(); // https://www.nesdev.org/wiki/CPU_unofficial_opcodes
    uint8_t ORA(); // Bitwise Logic OR
    uint8_t PHA(); // Push Accumulator to Stack
    uint8_t PHP(); // Push Status Register to Stack
    uint8_t PLA(); // Pop Accumulator off Stack
    uint8_t PLP(); // Pop Status Register off Stack
    uint8_t ROL();
    uint8_t ROR();
    uint8_t RTI();
    uint8_t RTS();
    uint8_t SBC();
    uint8_t SEC(); // Set Carry Flag
    uint8_t SED(); // Set Decimal Flag
    uint8_t SEI(); // Set Interrupt Flag / Enable Interrupts
    uint8_t STA(); // Store Accumulator at Address
    uint8_t STX(); // Store X Register at Address
    uint8_t STY(); // Store Y Register at Address
    uint8_t TAX(); // Transfer Accumulator to X Register
    uint8_t TAY(); // Transfer Accumulator to Y Register
    uint8_t TSX(); // Transfer Stack Pointer to X Register
    uint8_t TXA(); // Transfer X Register to Accumulator
    uint8_t TXS(); // Transfer X Register to Stack Pointer
    uint8_t TYA(); // Transfer Y Register to Accumulator

    uint8_t XXX(); // Illegal opcodes

    bool complete();

    std::map<uint16_t, std::string> disassemble(uint16_t nStart, uint16_t nStop);

    uint8_t fetch();
    uint8_t fetched = 0x00;
    uint16_t temp = 0x0000;
    uint16_t addr_abs = 0x0000;
    uint16_t addr_rel = 0x0000;
    uint8_t opcode = 0x00;
    uint8_t cycles = 0;

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
