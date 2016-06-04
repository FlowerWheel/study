#define Conn(x, y)	x##y
#define ToChar(x)	#@x
#define ToString(x) #x

#define MACRO  MacroValue
#undef  MACRO

#define Max(a, b) ( (a) > (b) ? (a) : (b) )
#define Min(a, b) ( (a) < (b) ? (a) : (b) )

#ifdef XXX
#else 
#endif


#define MEM_B(x) (*(byte *)(x))
#define MEM_W(x) (*(word *)(x))

#define FPOS(type, field) ( (dword)&((type *)0)->field )
#define FSIZ(type, field) ( sizeof (((type*)0)->field) )

#define WORD_LO(xxx) ( (byte) ( (word)(xxx) & 255 ) )
#define WORD_HI(xxx) ( (byte) ( (word)(xxx) >> 8 ) )

#define UPCASE(c) ( ((c) >= 'a' && (c) <= 'z') ? ((c) - 0x20) : (c) )

#define INC_SAT(val) ( val = ((val) + 1 > (val)) ? (val) + 1 : (val) )

#define ARR_SIZE(arr) ( sizeof((arr)) / sizeof((arr[0])) )
