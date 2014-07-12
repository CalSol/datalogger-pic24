/*
 * File:   datalogger-stringutil.c
 * Author: Ducky
 *
 * Created on August 13, 2011, 4:53 PM
 */

#include "../types.h"

#include "datalogger-stringutil.h"

inline void DlgStr_Init(DlgStr* dlgstr, char* str) {
    char* dest = dlgstr->string;
    char* destEnd = dlgstr->string + DLGSTR_MAX_LEN;
    
    while (dest < destEnd) {
        if (*str == 0) {
            break;
        }
        *dest = *str;
        dest++;
        str++;
    }
    
    dlgstr->pos = dest;
    dlgstr->end = destEnd;
}

inline void DlgStr_AppendString(DlgStr* dlgstr, char* appendStr) {
    char* dest = dlgstr->pos;
    char* destEnd = dlgstr->end;

    while (dest < destEnd) {
        if (*appendStr == 0) {
            break;
        }
        *dest = *appendStr;
        dest++;
        appendStr++;
    }

    dlgstr->pos = dest;
}

inline void DlgStr_AppendStringLen(DlgStr* dlgstr, char* appendStr, uint16_t len) {
    char* dest = dlgstr->pos;
    char* destEnd = dlgstr->pos + len;

    if (destEnd < dlgstr->end) {
        while (dest < destEnd) {
            *dest = *appendStr;
            dest++;
            appendStr++;
        }
        dlgstr->pos = destEnd;
    }
}

inline void DlgStr_AppendChar(DlgStr* dlgstr, char appendChar) {
    if (dlgstr->pos < dlgstr->end) {
        *dlgstr->pos = appendChar;
        dlgstr->pos += 1;
    }
}

char* DlgStr_MonthLookup[] = {
    "Jan", "Feb", "Mar", "Apr",
    "May", "Jun", "Jul", "Aug",
    "Sep", "Oct", "Nov", "Dec"
};
char* DlgStr_WeekdayLookup[] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

void DlgStr_AppendTmStruct(DlgStr* dlgstr, struct tm time) {
    DlgStr_AppendDec16(dlgstr, time.tm_year + 1900);
    DlgStr_AppendChar(dlgstr, ' ');
    DlgStr_AppendString(dlgstr, DlgStr_MonthLookup[time.tm_mon]);
    DlgStr_AppendChar(dlgstr, ' ');
    DlgStr_AppendDec16Pad(dlgstr, time.tm_mday, 2, ' ');
    DlgStr_AppendChar(dlgstr, ' ');
    DlgStr_AppendChar(dlgstr, '(');
    DlgStr_AppendString(dlgstr, DlgStr_WeekdayLookup[time.tm_wday]);
    DlgStr_AppendChar(dlgstr, ')');
    DlgStr_AppendChar(dlgstr, ' ');
    DlgStr_AppendDec16Pad(dlgstr, time.tm_hour, 2, '0');
    DlgStr_AppendChar(dlgstr, ':');
    DlgStr_AppendDec16Pad(dlgstr, time.tm_min, 2, '0');
    DlgStr_AppendChar(dlgstr, ':');
    DlgStr_AppendDec16Pad(dlgstr, time.tm_sec, 2, '0');
}

#define UINT22_MAX_CHAR 7
#define UINT10_MAX_CHAR 4
#define TIMESTAMP_MAX_CHAR (UINT22_MAX_CHAR + 1 + UINT10_MAX_CHAR)
void DlgStr_AppendTimestamp(DlgStr* dlgstr, uint32_t timestamp) {
    char* destPtr = dlgstr->pos;
    char* destLast = dlgstr->pos + TIMESTAMP_MAX_CHAR;
    
    if (destLast < dlgstr->end) {
        uint32_t timeSecs = timestamp >> 10;
        uint16_t timeFracSecs = timestamp & ((1<<10) - 1);

        char buf[UINT22_MAX_CHAR];
        char* bufPtr = buf;

        uint8_t i = 0;

        // Covnert seconds
        do {
            *bufPtr = (timeSecs % 10) + '0';
            bufPtr++;
            timeSecs /= 10;
        } while (timeSecs > 0);

        // Pad with whitespace
        i = UINT22_MAX_CHAR - (bufPtr - buf);
        while (i>0) {
            *destPtr = ' ';
            destPtr++;
            i--;
        }

        // Append secodns
        while (bufPtr > buf) {
            bufPtr--;
            *destPtr = *bufPtr;
            destPtr++;
        }
        
        // Append . between seconds and fraction seconds
        *destPtr = '.';
        destPtr++;

        // Convert fraction seconds
        do {
            *bufPtr = (timeFracSecs % 10) + '0';
            bufPtr++;
            timeFracSecs /= 10;
        } while (timeFracSecs > 0);

        // Pad with zeros
        i = UINT10_MAX_CHAR - (bufPtr - buf);
        while (i>0) {
            *destPtr = '0';
            destPtr++;
            i--;
        }

        // Append fraction secodns
        while (bufPtr > buf) {
            bufPtr--;
            *destPtr = *bufPtr;
            destPtr++;
        }

        dlgstr->pos = destPtr;
    }
}

void DlgStr_AppendDec32(DlgStr* dlgstr, int32_t appendInt) {
    char buf[INT32_MAX_CHAR];
    char* bufPtr = buf;
    uint8_t neg;

    if (appendInt < 0) {
        neg = 1;
        appendInt = -appendInt;
    } else {
        neg = 0;
    }

    do {
        *bufPtr = (appendInt % 10) + '0';
        bufPtr++;
        appendInt /= 10;
    } while (appendInt > 0);

    uint8_t len = bufPtr - buf;
    if (neg) {
        len += 1;
    }

    if (dlgstr->pos < dlgstr->end - len) {
        char* destPtr = dlgstr->pos;
        dlgstr->pos += len;
        if (neg) {
            *destPtr = '-';
            destPtr++;
        }
        while (bufPtr > buf) {
            bufPtr--;
            *destPtr = *bufPtr;
            destPtr++;
        }
    }
}

void DlgStr_AppendUDec16(DlgStr* dlgstr, uint16_t appendInt) {
    char buf[INT16_MAX_CHAR];
    char* bufPtr = buf;

    do {
        *bufPtr = (appendInt % 10) + '0';
        bufPtr++;
        appendInt /= 10;
    } while (appendInt > 0);

    uint8_t len = bufPtr - buf;

    if (dlgstr->pos < dlgstr->end - len) {
        char* destPtr = dlgstr->pos;

        while (bufPtr > buf) {
            bufPtr--;
            *destPtr = *bufPtr;
            destPtr++;
        }
        dlgstr->pos = destPtr;
    }
}

void DlgStr_AppendDec16(DlgStr* dlgstr, int16_t appendInt) {
    char buf[INT16_MAX_CHAR];
    char* bufPtr = buf;
    uint8_t neg;

    if (appendInt < 0) {
        neg = 1;
        appendInt = -appendInt;
    } else {
        neg = 0;
    }

    do {
        *bufPtr = (appendInt % 10) + '0';
        bufPtr++;
        appendInt /= 10;
    } while (appendInt > 0);

    uint8_t len = bufPtr - buf;
    if (neg) {
        len += 1;
    }

    if (dlgstr->pos < dlgstr->end - len) {
        char* destPtr = dlgstr->pos;
        if (neg) {
            *destPtr = '-';
            destPtr++;
        }
        while (bufPtr > buf) {
            bufPtr--;
            *destPtr = *bufPtr;
            destPtr++;
        }
        dlgstr->pos = destPtr;
    }
}

void DlgStr_AppendDec16Dec(DlgStr* dlgstr, int16_t appendInt, uint8_t dec) {
    char buf[INT16_MAX_CHAR];
    char* bufPtr = buf;
    uint8_t neg;

    if (appendInt < 0) {
        neg = 1;
        appendInt = -appendInt;
    } else {
        neg = 0;
    }

    do {
        *bufPtr = (appendInt % 10) + '0';
        bufPtr++;
        appendInt /= 10;
    } while (appendInt > 0);

    uint8_t len = bufPtr - buf;
    uint8_t finalLen;
    if (len <= dec) {
        finalLen = dec + 2;
    } else {
        finalLen = len + 1;
    }
    if (neg) {
        finalLen += 1;
    }
    
    if (dlgstr->pos < dlgstr->end - len) {
        char* destPtr = dlgstr->pos;
        if (neg) {
            *destPtr = '-';
            destPtr++;
        }
        if (len <= dec) {
            *destPtr = '0';
            destPtr++;
            *destPtr = '.';
            destPtr++;
            while (len < dec) {
                *destPtr = '0';
                destPtr++;
                len++;
            }
            while (bufPtr > buf) {
                bufPtr--;
                *destPtr = *bufPtr;
                destPtr++;
            }
        } else {
            while (bufPtr > buf) {
                if (len == dec) {
                    *destPtr = '.';
                    destPtr++;
                }
                len--;
                bufPtr--;
                *destPtr = *bufPtr;
                destPtr++;
            }
        }

        dlgstr->pos = destPtr;
    }
}

void DlgStr_AppendDec16Pad(DlgStr* dlgstr, int16_t appendInt, uint8_t minLen, char pad) {
    char buf[INT16_MAX_CHAR];
    char* bufPtr = buf;
    uint8_t neg;

    if (appendInt < 0) {
        neg = 1;
        appendInt = -appendInt;
    } else {
        neg = 0;
    }

    do {
        *bufPtr = (appendInt % 10) + '0';
        bufPtr++;
        appendInt /= 10;
    } while (appendInt > 0);

    uint8_t len = bufPtr - buf;
    if (neg) {
        len += 1;
    }
    uint8_t finalLen = minLen > len? minLen : len;
    
    if (dlgstr->pos < dlgstr->end - finalLen) {
        char* destPtr = dlgstr->pos;
        if (neg) {
            *destPtr = '-';
            destPtr++;
        }
        while (minLen > len) {
            *destPtr = pad;
            destPtr++;
            minLen--;
        }
        while (bufPtr > buf) {
            bufPtr--;
            *destPtr = *bufPtr;
            destPtr++;
        }
        dlgstr->pos = destPtr;
    }
}

void DlgStr_AppendHex32(DlgStr* dlgstr, uint32_t appendInt) {
    if (dlgstr->pos < dlgstr->end - 8) {
        dlgstr->pos += 8;
        char* dest = dlgstr->pos;
        char chr;

        dest--;
        chr = appendInt & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
        dest--;
        chr = (appendInt >> 4) & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
        dest--;
        chr = (appendInt >> 8) & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
        dest--;
        chr = (appendInt >> 12) & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
        dest--;
        chr = (appendInt >> 16) & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
        dest--;
        chr = (appendInt >> 20) & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
        dest--;
        chr = (appendInt >> 24) & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
        dest--;
        chr = (appendInt >> 28) & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
    }
}

void DlgStr_AppendHex16(DlgStr* dlgstr, uint16_t appendInt) {
    if (dlgstr->pos < dlgstr->end - 4) {
        dlgstr->pos += 4;
        char* dest = dlgstr->pos;
        char chr;

        dest--;
        chr = appendInt & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
        dest--;
        chr = (appendInt >> 4) & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
        dest--;
        chr = (appendInt >> 8) & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
        dest--;
        chr = (appendInt >> 12) & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
    }
}

void DlgStr_AppendHex12(DlgStr* dlgstr, uint16_t appendInt) {
    if (dlgstr->pos < dlgstr->end - 3) {
        dlgstr->pos += 3;
        char* dest = dlgstr->pos;
        char chr;

        dest--;
        chr = appendInt & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
        dest--;
        chr = (appendInt >> 4) & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
        dest--;
        chr = (appendInt >> 8) & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
    }
}

void DlgStr_AppendHex8(DlgStr* dlgstr, uint8_t appendInt) {
    if (dlgstr->pos < dlgstr->end - 2) {
        dlgstr->pos += 2;
        char* dest = dlgstr->pos;
        char chr;

        dest--;
        chr = appendInt & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
        dest--;
        chr = (appendInt >> 4) & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
    }
}

void DlgStr_AppendHex4(DlgStr* dlgstr, uint8_t appendInt) {
    if (dlgstr->pos < dlgstr->end - 1) {
        dlgstr->pos += 1;
        char* dest = dlgstr->pos;
        char chr;

        dest--;
        chr = appendInt & 0x0f;
        if (chr < 0x0a) {	*dest = chr + '0';
        } else {			*dest = chr + '7';
        }
    }
}

char* Int32ToString(uint32_t input, char *buffer) {
	uint8_t chr;
	chr = input & 0x0f;
	if (chr < 0x0a) {	buffer[7] = chr + '0';
	} else {			buffer[7] = chr + '7';
	}					chr = (input >> 4) & 0x0f;
	if (chr < 0x0a) {	buffer[6] = chr + '0';
	} else {			buffer[6] = chr + '7';
	}					chr = (input >> 8) & 0x0f;
	if (chr < 0x0a) {	buffer[5] = chr + '0';
	} else {			buffer[5] = chr + '7';
	}					chr = (input >> 12) & 0x0f;
	if (chr < 0x0a) {	buffer[4] = chr + '0';
	} else {			buffer[4] = chr + '7';
	}					chr = (input >> 16) & 0x0f;
	if (chr < 0x0a) {	buffer[3] = chr + '0';
	} else {			buffer[3] = chr + '7';
	}					chr = (input >> 20) & 0x0f;
	if (chr < 0x0a) {	buffer[2] = chr + '0';
	} else {			buffer[2] = chr + '7';
	}					chr = (input >> 24) & 0x0f;
	if (chr < 0x0a) {	buffer[1] = chr + '0';
	} else {			buffer[1] = chr + '7';
	}					chr = (input >> 28) & 0x0f;
	if (chr < 0x0a) {	buffer[0] = chr + '0';
	} else {			buffer[0] = chr + '7';
	}
	return buffer;
}

char* Int16ToString(uint16_t input, char *buffer) {
	uint8_t chr;
	chr = input & 0x0f;
	if (chr < 0x0a) {	buffer[3] = chr + '0';
	} else {			buffer[3] = chr + '7';
	}					chr = (input >> 4) & 0x0f;
	if (chr < 0x0a) {	buffer[2] = chr + '0';
	} else {			buffer[2] = chr + '7';
	}					chr = (input >> 8) & 0x0f;
	if (chr < 0x0a) {	buffer[1] = chr + '0';
	} else {			buffer[1] = chr + '7';
	}					chr = (input >> 12) & 0x0f;
	if (chr < 0x0a) {	buffer[0] = chr + '0';
	} else {			buffer[0] = chr + '7';
	}
	return buffer;
}

char* Int12ToString(uint16_t input, char *buffer) {
	uint8_t chr;
	chr = input & 0x0f;
	if (chr < 0x0a) {	buffer[2] = chr + '0';
	} else {			buffer[2] = chr + '7';
	}					chr = (input >> 4) & 0x0f;
	if (chr < 0x0a) {	buffer[1] = chr + '0';
	} else {			buffer[1] = chr + '7';
	}					chr = (input >> 8) & 0x0f;
	if (chr < 0x0a) {	buffer[0] = chr + '0';
	} else {			buffer[0] = chr + '7';
	}
	return buffer;
}

char* Int8ToString(uint8_t input, char *buffer) {
	uint8_t chr;
	chr = input & 0x0f;
	if (chr < 0x0a) {	buffer[1] = chr + '0';
	} else {			buffer[1] = chr + '7';
	}					chr = (input >> 4) & 0x0f;
	if (chr < 0x0a) {	buffer[0] = chr + '0';
	} else {			buffer[0] = chr + '7';
	}
	return buffer;
}

char* Int4ToString(uint8_t input, char *buffer) {
	uint8_t chr;
	chr = input & 0x0f;
	if (chr < 0x0a) {	buffer[0] = chr + '0';
	} else {			buffer[0] = chr + '7';
	}
	return buffer;
}
