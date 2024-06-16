#include "../includes/Ppu.hpp"
#include "../includes/Byte.hpp"

Ppu::Ppu()
{
	_palScreen[0x00] = sf::Color(84, 84, 84);
	_palScreen[0x01] = sf::Color(0, 30, 116);
	_palScreen[0x02] = sf::Color(8, 16, 144);
	_palScreen[0x03] = sf::Color(48, 0, 136);
	_palScreen[0x04] = sf::Color(68, 0, 100);
	_palScreen[0x05] = sf::Color(92, 0, 48);
	_palScreen[0x06] = sf::Color(84, 4, 0);
	_palScreen[0x07] = sf::Color(60, 24, 0);
	_palScreen[0x08] = sf::Color(32, 42, 0);
	_palScreen[0x09] = sf::Color(8, 58, 0);
	_palScreen[0x0A] = sf::Color(0, 64, 0);
	_palScreen[0x0B] = sf::Color(0, 60, 0);
	_palScreen[0x0C] = sf::Color(0, 50, 60);
	_palScreen[0x0D] = sf::Color(0, 0, 0);
	_palScreen[0x0E] = sf::Color(0, 0, 0);
	_palScreen[0x0F] = sf::Color(0, 0, 0);
	_palScreen[0x10] = sf::Color(152, 150, 152);
	_palScreen[0x11] = sf::Color(8, 76, 196);
	_palScreen[0x12] = sf::Color(48, 50, 236);
	_palScreen[0x13] = sf::Color(92, 30, 228);
	_palScreen[0x14] = sf::Color(136, 20, 176);
	_palScreen[0x15] = sf::Color(160, 20, 100);
	_palScreen[0x16] = sf::Color(152, 34, 32);
	_palScreen[0x17] = sf::Color(120, 60, 0);
	_palScreen[0x18] = sf::Color(84, 90, 0);
	_palScreen[0x19] = sf::Color(40, 114, 0);
	_palScreen[0x1A] = sf::Color(8, 124, 0);
	_palScreen[0x1B] = sf::Color(0, 118, 40);
	_palScreen[0x1C] = sf::Color(0, 102, 120);
	_palScreen[0x1D] = sf::Color(0, 0, 0);
	_palScreen[0x1E] = sf::Color(0, 0, 0);
	_palScreen[0x1F] = sf::Color(0, 0, 0);
	_palScreen[0x20] = sf::Color(236, 238, 236);
	_palScreen[0x21] = sf::Color(76, 154, 236);
	_palScreen[0x22] = sf::Color(120, 124, 236);
	_palScreen[0x23] = sf::Color(176, 98, 236);
	_palScreen[0x24] = sf::Color(228, 84, 236);
	_palScreen[0x25] = sf::Color(236, 88, 180);
	_palScreen[0x26] = sf::Color(236, 106, 100);
	_palScreen[0x27] = sf::Color(212, 136, 32);
	_palScreen[0x28] = sf::Color(160, 170, 0);
	_palScreen[0x29] = sf::Color(116, 196, 0);
	_palScreen[0x2A] = sf::Color(76, 208, 32);
	_palScreen[0x2B] = sf::Color(56, 204, 108);
	_palScreen[0x2C] = sf::Color(56, 180, 204);
	_palScreen[0x2D] = sf::Color(60, 60, 60);
	_palScreen[0x2E] = sf::Color(0, 0, 0);
	_palScreen[0x2F] = sf::Color(0, 0, 0);
	_palScreen[0x30] = sf::Color(236, 238, 236);
	_palScreen[0x31] = sf::Color(168, 204, 236);
	_palScreen[0x32] = sf::Color(188, 188, 236);
	_palScreen[0x33] = sf::Color(212, 178, 236);
	_palScreen[0x34] = sf::Color(236, 174, 236);
	_palScreen[0x35] = sf::Color(236, 174, 212);
	_palScreen[0x36] = sf::Color(236, 180, 176);
	_palScreen[0x37] = sf::Color(228, 196, 144);
	_palScreen[0x38] = sf::Color(204, 210, 120);
	_palScreen[0x39] = sf::Color(180, 222, 120);
	_palScreen[0x3A] = sf::Color(168, 226, 144);
	_palScreen[0x3B] = sf::Color(152, 226, 180);
	_palScreen[0x3C] = sf::Color(160, 214, 228);
	_palScreen[0x3D] = sf::Color(160, 162, 160);
	_palScreen[0x3E] = sf::Color(0, 0, 0);
	_palScreen[0x3F] = sf::Color(0, 0, 0);
    sprScreen.create(256, 240);
	sprPatternTable[0].create(128, 128);
	sprPatternTable[1].create(128, 128);
}

Ppu::~Ppu() {}

sf::Image& Ppu::GetScreen()
{
	return sprScreen;
}

sf::Image &Ppu::getPatternTable(uint8_t i, uint8_t palette)
{
	for (uint16_t _tileY = 0; _tileY < 16; ++_tileY) {
		for (uint16_t _tileX = 0; _tileX < 16; ++_tileX) {
			uint16_t nOffset = _tileY * 256 + _tileX * 16;
			for (uint16_t row = 0; row < 8; ++row) {
				uint8_t tile_lsb = ppuRead(i * 0x1000 + nOffset + row);
				uint8_t tile_msb = ppuRead(i * 0x1000 + nOffset + row + 0x0008);
				for (uint16_t col = 0; col < 8; ++col) {
					uint8_t pixel = ((tile_lsb & 0x01) << 1) | (tile_msb & 0x01);
					tile_lsb >>= 1;
                    tile_msb >>= 1;
					sprPatternTable[i].setPixel(
						_tileX * 8 + (7 - col),
						_tileY * 8 + row,
						GetColorFromPaletteRam(palette, pixel)
					);
				}
			}
		}
	}
    return sprPatternTable[i];
}

sf::Color Ppu::GetColorFromPaletteRam(uint8_t palette, uint8_t pixel)
{
	return _palScreen[ppuRead(0x3F00 + (palette << 2) + pixel) & 0x3F];
}

uint8_t Ppu::cpuRead(uint16_t addr, bool rdonly)
{
	uint8_t data = 0x00;

	if (rdonly) {
		switch (addr) {
		case 0x0000: // Control
			data = control.reg;
			break;
		case 0x0001: // Mask
			data = mask.reg;
			break;
		case 0x0002: // Status
			data = status.reg;
			break;
		case 0x0003: // OAM Address
			break;
		case 0x0004: // OAM Data
			break;
		case 0x0005: // Scroll
			break;
		case 0x0006: // PPU Address
			break;
		case 0x0007: // PPU Data
			break;
		}
	} else {
		switch (addr) {
        case 0x0000: // Control - Not readable
            break;
		case 0x0001: // Mask - Not Readable
            break;
		case 0x0002: // Status
			data = (status.reg & 0xE0) | (_ppuDataBuffer & 0x1F);
			status.vertical_blank = 0;
			_addressLatch = 0;
			break;
		case 0x0003: // OAM Address
            break;
		case 0x0004: // OAM Data
            data = OAMPtr[oam_addr];
                break;
		case 0x0005: // Scroll - Not Readable
            break;
		case 0x0006: // PPU Address - Not Readable
            break;
		case 0x0007: // PPU Data
			data = _ppuDataBuffer;
			_ppuDataBuffer = ppuRead(_vramAddr.reg);
			if (_vramAddr.reg >= 0x3F00)
                data = _ppuDataBuffer;
			_vramAddr.reg += (control.increment_mode ? 32 : 1);
			break;
		}
	}
	return data;
}

void Ppu::cpuWrite(uint16_t addr, uint8_t data)
{
	switch (addr) {
	case 0x0000: // Control
		control.reg = data;
		_tramAddr.nametable_x = control.nametable_x;
		_tramAddr.nametable_y = control.nametable_y;
		break;
	case 0x0001: // Mask
		mask.reg = data;
		break;
	case 0x0002: // Status
		break;
	case 0x0003: // OAM Address
        oam_addr = data;
		break;
	case 0x0004: // OAM Data
        OAMPtr[oam_addr] = data;
		break;
	case 0x0005: // Scroll
		if (_addressLatch == 0) {
			_fineX = data & 0x07;
			_tramAddr.coarse_x = data >> 3;
			_addressLatch = 1;
		} else {
			_tramAddr.fine_y = data & 0x07;
			_tramAddr.coarse_y = data >> 3;
			_addressLatch = 0;
		}
		break;
	case 0x0006: // PPU Address
		if (_addressLatch == 0) {
			_tramAddr.reg = (uint16_t)((data & 0x3F) << 8) | (_tramAddr.reg & 0x00FF);
			_addressLatch = 1;
		} else {
			_tramAddr.reg = (_tramAddr.reg & 0xFF00) | data;
			_vramAddr = _tramAddr;
			_addressLatch = 0;
		}
		break;
	case 0x0007: // PPU Data
		ppuWrite(_vramAddr.reg, data);
		_vramAddr.reg += (control.increment_mode ? 32 : 1);
		break;
	}
}

uint8_t Ppu::ppuRead(uint16_t addr, bool rdonly)
{
	uint8_t data = 0x00;
	addr &= 0x3FFF;

	if (cart->ppuRead(addr, data)) {}
	else if (addr >= 0x0000 && addr <= 0x1FFF)
		data = tblPattern[(addr & 0x1000) >> 12][addr & 0x0FFF];
	else if (addr >= 0x2000 && addr <= 0x3EFF) {
		addr &= 0x0FFF;
		if (cart->mirror == Cartridge::MIRROR::VERTICAL) {
			if (addr >= 0x0000 && addr <= 0x03FF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0400 && addr <= 0x07FF)
				data = tblName[1][addr & 0x03FF];
			if (addr >= 0x0800 && addr <= 0x0BFF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				data = tblName[1][addr & 0x03FF];
		} else if (cart->mirror == Cartridge::MIRROR::HORIZONTAL) {
			if (addr >= 0x0000 && addr <= 0x03FF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0400 && addr <= 0x07FF)
				data = tblName[0][addr & 0x03FF];
			if (addr >= 0x0800 && addr <= 0x0BFF)
				data = tblName[1][addr & 0x03FF];
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				data = tblName[1][addr & 0x03FF];
		}
	} else if (addr >= 0x3F00 && addr <= 0x3FFF) {
		addr &= 0x001F;
		if (addr == 0x0010 || addr == 0x0014 || addr == 0x0018 || addr == 0x001C)
            addr -= 0x0010;
		data = tblPalette[addr] & (mask.grayscale ? 0x30 : 0x3F);
	}
	return data;
}

void Ppu::ppuWrite(uint16_t addr, uint8_t data)
{
	addr &= 0x3FFF;
	if (cart->ppuWrite(addr, data)) {}
	else if (addr >= 0x0000 && addr <= 0x1FFF)
		tblPattern[(addr & 0x1000) >> 12][addr & 0x0FFF] = data;
	else if (addr >= 0x2000 && addr <= 0x3EFF) {
		addr &= 0x0FFF;
        if (cart->mirror == Cartridge::MIRROR::VERTICAL){
			if (addr >= 0x0000 && addr <= 0x03FF)
				tblName[0][addr & 0x03FF] = data;
			if (addr >= 0x0400 && addr <= 0x07FF)
				tblName[1][addr & 0x03FF] = data;
			if (addr >= 0x0800 && addr <= 0x0BFF)
				tblName[0][addr & 0x03FF] = data;
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				tblName[1][addr & 0x03FF] = data;
		} else if (cart->mirror == Cartridge::MIRROR::HORIZONTAL) {
			if (addr >= 0x0000 && addr <= 0x03FF)
				tblName[0][addr & 0x03FF] = data;
			if (addr >= 0x0400 && addr <= 0x07FF)
				tblName[0][addr & 0x03FF] = data;
			if (addr >= 0x0800 && addr <= 0x0BFF)
				tblName[1][addr & 0x03FF] = data;
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				tblName[1][addr & 0x03FF] = data;
		}
	} else if (addr >= 0x3F00 && addr <= 0x3FFF) {
		addr &= 0x001F;
        if (addr == 0x0010 || addr == 0x0014 || addr == 0x0018 || addr == 0x001C)
            addr -= 0x0010;
		tblPalette[addr] = data;
	}
}

void Ppu::connectCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	cart = cartridge;
}

void Ppu::reset()
{
	_fineX = 0x00;
	_addressLatch = 0x00;
	_ppuDataBuffer = 0x00;
	_scanline = 0;
	_cycle = 0;
	_bgNextTileId = 0x00;
	_bgNextTileAttribute = 0x00;
	_bgNextTileLst = 0x00;
	_bgNextTileMsb = 0x00;
	_bgShifterPatternLow = 0x0000;
	_bgShifterPatternHigh = 0x0000;
	_bgShifterAttributeLow = 0x0000;
	_bgShifterAttributeHigh = 0x0000;
	status.reg = 0x00;
	mask.reg = 0x00;
	control.reg = 0x00;
	_vramAddr.reg = 0x0000;
	_tramAddr.reg = 0x0000;
}

void Ppu::clock()
{
	static auto IncrementScrollX = [&]() {
		if (mask.render_background || mask.render_sprites) {
			if (_vramAddr.coarse_x == 31) {
				_vramAddr.coarse_x = 0;
				_vramAddr.nametable_x = ~_vramAddr.nametable_x;
			} else {
				_vramAddr.coarse_x++;
			}
		}
	};

	static auto IncrementScrollY = [&]() {
		if (!(mask.render_background || mask.render_sprites))
			return;
        if (_vramAddr.fine_y < 7)
            ++_vramAddr.fine_y;
        else {
            _vramAddr.fine_y = 0;
            if (_vramAddr.coarse_y == 29) {
                _vramAddr.coarse_y = 0;
                _vramAddr.nametable_y = ~_vramAddr.nametable_y;
            } else if (_vramAddr.coarse_y == 31)
                _vramAddr.coarse_y = 0;
            else
                ++_vramAddr.coarse_y;
        }
	};

	static auto TransferAddressX = [&]() {
		if (mask.render_background || mask.render_sprites) {
			_vramAddr.nametable_x = _tramAddr.nametable_x;
			_vramAddr.coarse_x = _tramAddr.coarse_x;
		}
	};

	static auto TransferAddressY = [&]() {
		if (mask.render_background || mask.render_sprites) {
			_vramAddr.fine_y = _tramAddr.fine_y;
			_vramAddr.nametable_y = _tramAddr.nametable_y;
			_vramAddr.coarse_y = _tramAddr.coarse_y;
		}
	};

	static auto LoadBackgroundShifters = [&]() {
		_bgShifterPatternLow = (_bgShifterPatternLow & 0xFF00) | _bgNextTileLst;
		_bgShifterPatternHigh = (_bgShifterPatternHigh & 0xFF00) | _bgNextTileMsb;
		_bgShifterAttributeLow = (_bgShifterAttributeLow & 0xFF00) | ((_bgNextTileAttribute & 0b01) ? 0xFF : 0x00);
		_bgShifterAttributeHigh = (_bgShifterAttributeHigh & 0xFF00) | ((_bgNextTileAttribute & 0b10) ? 0xFF : 0x00);
	};

	static auto UpdateShifters = [&](){
		if (mask.render_background) {
			_bgShifterPatternLow <<= 1;
			_bgShifterPatternHigh <<= 1;
			_bgShifterAttributeLow <<= 1;
			_bgShifterAttributeHigh <<= 1;
		}
        if (mask.render_sprites && _cycle >= 1 && _cycle <= 258) {
            for (int i = 0; i < sprite_count; ++i) {
                if (spriteScanline[i].x > 0)
                    --spriteScanline[i].x;
                else {
                    sprite_shifter_pattern_lo[i] <<= 1;
                    sprite_shifter_pattern_hi[i] <<= 1;
                }
            }
        }
	};

	if (_scanline >= -1 && _scanline < 240) {
		if (_scanline == -1 && _cycle == 1) {
			status.vertical_blank = 0;
            status.sprite_overflow = 0;
            status.sprite_zero_hit = 0;
            for (int i = 0; i < 8; ++i) {
                sprite_shifter_pattern_lo[i] = 0;
                sprite_shifter_pattern_hi[i] = 0;
            }
		}
		if ((_cycle >= 2 && _cycle < 258) || (_cycle >= 321 && _cycle < 338)) {
			UpdateShifters();
			switch ((_cycle - 1) % 8) {
			case 0:
				LoadBackgroundShifters();
				_bgNextTileId = ppuRead(0x2000 | (_vramAddr.reg & 0x0FFF));
				break;
			case 2:
				_bgNextTileAttribute = ppuRead(0x23C0 | (_vramAddr.nametable_y << 11)
					                                 | (_vramAddr.nametable_x << 10)
					                                 | ((_vramAddr.coarse_y >> 2) << 3)
					                                 | (_vramAddr.coarse_x >> 2));
				if (_vramAddr.coarse_y & 0x02)
                    _bgNextTileAttribute >>= 4;
				if (_vramAddr.coarse_x & 0x02)
                    _bgNextTileAttribute >>= 2;
				_bgNextTileAttribute &= 0x03;
				break;
			case 4:
				_bgNextTileLst = ppuRead((control.pattern_background << 12)
					                       + ((uint16_t)_bgNextTileId << 4)
					                       + (_vramAddr.fine_y) + 0);
				break;
			case 6:
				_bgNextTileMsb = ppuRead((control.pattern_background << 12)
					                       + ((uint16_t)_bgNextTileId << 4)
					                       + (_vramAddr.fine_y) + 8);
				break;
			case 7:
				IncrementScrollX();
				break;
			}
		}
		if (_cycle == 256)
			IncrementScrollY();
		if (_cycle == 257) {
			LoadBackgroundShifters();
			TransferAddressX();
		}
		if (_cycle == 338 || _cycle == 340)
			_bgNextTileId = ppuRead(0x2000 | (_vramAddr.reg & 0x0FFF));
        if (_cycle == 257 && _scanline >= 0) {
            memset(spriteScanline, 0xFF, 8 * sizeof(sObjectAttributeEntry));
            sprite_count = 0;
            spriteZeroHitPossible = false;
            for (uint8_t nOAMEntry = 0; nOAMEntry < 64 && sprite_count < 9; ++nOAMEntry) {
                int16_t diff = ((int16_t)_scanline - (int16_t)OAM[nOAMEntry].y);
                if (!(diff >= 0 && diff < (control.sprite_size ? 16 : 8)))
                    continue;
                if (sprite_count < 8) {
                    if (nOAMEntry == 0)
                        spriteZeroHitPossible = true;
                    memcpy(&spriteScanline[sprite_count], &OAM[nOAMEntry], sizeof(sObjectAttributeEntry));
                    ++sprite_count;
                }
            }
            status.sprite_overflow = (sprite_count > 8);
        }
        if (_cycle == 340) {
            for (uint8_t i = 0; i < sprite_count; ++i) {
                uint8_t sprite_patterns_bits_lo, sprite_patterns_bits_hi;
                uint16_t sprite_patterns_addr_lo, sprite_patterns_addr_hi;
                if (!control.sprite_size) {
                    if (!(spriteScanline[i].attribute & 0x80)) {
                        sprite_patterns_addr_lo =
                                (control.pattern_sprite << 12)
                                | (spriteScanline[i].id << 4)
                                | (_scanline - spriteScanline[i].y);
                    } else {
                        sprite_patterns_addr_lo =
                                (control.pattern_sprite << 12)
                                | (spriteScanline[i].id << 4)
                                | (7 - (_scanline - spriteScanline[i].y));
                    }
                } else {
                    if (!(spriteScanline[i].attribute & 0x80)) {
                        if (_scanline - spriteScanline[i].y < 8) {
                            sprite_patterns_addr_lo =
                                    ((spriteScanline[i].id & 0x01) << 12)
                                    | ((spriteScanline[i].id & 0xFE) << 4)
                                    | ((_scanline - spriteScanline[i].y) & 0x07);
                        } else {
                            sprite_patterns_addr_lo =
                                    ((spriteScanline[i].id & 0x01) << 12)
                                    | (((spriteScanline[i].id & 0xFE) + 1) << 4)
                                    | ((_scanline - spriteScanline[i].y) & 0x07);
                        }
                    } else {
                        if (_scanline - spriteScanline[i].y < 8) {
                            sprite_patterns_addr_lo =
                                    ((spriteScanline[i].id & 0x01) << 12)
                                    | (((spriteScanline[i].id & 0xFE) + 1) << 4)
                                    | (7 - (_scanline - spriteScanline[i].y) & 0x07);
                        } else {
                            sprite_patterns_addr_lo =
                                    ((spriteScanline[i].id & 0x01) << 12)
                                    | ((spriteScanline[i].id & 0xFE) << 4)
                                    | (7 - (_scanline - spriteScanline[i].y) & 0x07);
                        }
                    }
                }
                sprite_patterns_addr_hi = sprite_patterns_addr_lo + 8;
                sprite_patterns_bits_lo = ppuRead(sprite_patterns_addr_lo);
                sprite_patterns_bits_hi = ppuRead(sprite_patterns_addr_hi);
                if (spriteScanline[i].attribute & 0x40) {
                    sprite_patterns_bits_lo = Byte::flipByte(sprite_patterns_bits_lo);
                    sprite_patterns_bits_hi = Byte::flipByte(sprite_patterns_bits_hi);
                }
                sprite_shifter_pattern_lo[i] = sprite_patterns_bits_lo;
                sprite_shifter_pattern_hi[i] = sprite_patterns_bits_hi;
            }
        }
		if (_scanline == -1 && _cycle >= 280 && _cycle < 305)
			TransferAddressY();
	}
	if (_scanline >= 241 && _scanline < 261) {
		if (_scanline == 241 && _cycle == 1) {
			status.vertical_blank = 1;
            nmi = control.enable_nmi;
		}
	}
	uint8_t bg_pixel = 0x00;
	uint8_t bg_palette = 0x00;
	if (mask.render_background) {
		uint16_t bit_mux = 0x8000 >> _fineX;
		uint8_t p0_pixel = (_bgShifterPatternLow & bit_mux) > 0;
		uint8_t p1_pixel = (_bgShifterPatternHigh & bit_mux) > 0;
		bg_pixel = (p1_pixel << 1) | p0_pixel;
		uint8_t bg_pal0 = (_bgShifterAttributeLow & bit_mux) > 0;
		uint8_t bg_pal1 = (_bgShifterAttributeHigh & bit_mux) > 0;
		bg_palette = (bg_pal1 << 1) | bg_pal0;
	}

    uint8_t fg_pixel = 0x00;
    uint8_t fg_palette = 0x00;
    uint8_t fg_priority = 0x00;

    if (mask.render_sprites) {
        spriteZeroBeingRendered = false;
        for (uint8_t i = 0; i < sprite_count; ++i) {
            if (spriteScanline[i].x == 0) {
                uint8_t fg_pixel_lo = (sprite_shifter_pattern_lo[i] & 0x80) > 0;
                uint8_t fg_pixel_hi = (sprite_shifter_pattern_hi[i] & 0x80) > 0;
                fg_pixel = (fg_pixel_hi << 1) | fg_pixel_lo;
                fg_palette = (spriteScanline[i].attribute & 0x03) + 0x04;
                fg_priority = (spriteScanline[i].attribute & 0x20) == 0;
                if (fg_pixel != 0) {
                    if (i == 0)
                        spriteZeroBeingRendered = true;
                    break;
                }
            }
        }
    }

    uint8_t pixel = 0x00;
    uint8_t palette = 0x00;

    if (bg_pixel == 0 && fg_pixel == 0) {
        pixel = 0x00;
        palette = 0x00;
    }
    if (bg_pixel == 0 && fg_pixel > 0) {
        pixel = fg_pixel;
        palette = fg_palette;
    }
    if (bg_pixel > 0 && fg_pixel == 0) {
        pixel = bg_pixel;
        palette = bg_palette;
    }
    if (bg_pixel > 0 && fg_pixel > 0) {
        if (fg_priority) {
            pixel = fg_pixel;
            palette = fg_palette;
        } else {
            pixel = bg_pixel;
            palette = bg_pixel;
        }
        if (spriteZeroHitPossible && spriteZeroBeingRendered) {
            if (mask.render_background & mask.render_sprites) {
                if (~(mask.render_background_left | mask.render_sprites_left)) {
                     if (_cycle >= 9 && _cycle < 258) {
                         status.sprite_zero_hit = 1;
                     }
                } else {
                    if (_cycle >= 1 && _cycle < 258) {
                        status.sprite_zero_hit = 1;
                    }
                }
            }
        }
    }
    int x = _cycle - 1;
    int y = _scanline;
    int width = sprScreen.getSize().x;
    int height = sprScreen.getSize().y;
    if (x >= 0 && x < width && y >= 0 && y < height)
        sprScreen.setPixel(x, y, GetColorFromPaletteRam(palette, pixel));
	++_cycle;
	if (_cycle >= 341) {
		_cycle = 0;
		++_scanline;
		if (_scanline >= 261) {
			_scanline = -1;
			frame_complete = true;
		}
	}
}
