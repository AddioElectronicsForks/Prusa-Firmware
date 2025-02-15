//menu.h
#ifndef _MENU_H
#define _MENU_H

#include <inttypes.h>
#include "eeprom.h"

#define MENU_DATA_SIZE      32

//Function pointer to menu functions.
typedef void (*menu_func_t)(void);

typedef struct 
{
    menu_func_t menu;
    int8_t position;
} menu_record_t;

typedef struct
{
    //Variables used when editing values.
    const char* editLabel;
    void* editValue;
    int16_t currentValue;
    int16_t minEditValue;
    int16_t maxEditValue;
} menu_data_edit_t;

extern uint8_t menu_data[MENU_DATA_SIZE];

extern uint8_t menu_depth;

//! definition of reasons blocking the main menu
//! Use them as bit mask, so that the code may set various errors at the same time
enum ESeriousErrors {
	MENU_BLOCK_NONE                = 0,
	MENU_BLOCK_THERMAL_ERROR       = 0x01,
#ifdef TEMP_MODEL
	MENU_BLOCK_TEMP_MODEL_AUTOTUNE = 0x02,
#endif
    MENU_BLOCK_STATUS_SCREEN_M0    = 0x04,
}; // and possibly others in the future.

//! this is a flag for disabling entering the main menu and longpress. If this is set to anything !=
//! 0, the only the main status screen will be shown on the LCD and the user will be prevented from
//! entering the menu.
extern uint8_t menu_block_mask;

//! a pair of macros for manipulating menu entry
//! a c++ class would have been better
#define menu_set_block(x) menu_block_mask |= x;
#define menu_unset_block(x) menu_block_mask &= ~x;
#define menu_is_blocked(x) (menu_block_mask & x)
#define menu_is_any_block() (menu_block_mask != MENU_BLOCK_NONE)

extern uint8_t menu_line;
extern uint8_t menu_item;
extern uint8_t menu_row;

//scroll offset in the current menu
extern uint8_t menu_top;
extern uint8_t menu_clicked;
extern uint8_t menu_leaving;

//function pointer to the currently active menu
extern menu_func_t menu_menu;

extern void menu_data_reset(void);

extern void menu_goto(menu_func_t menu, const int16_t encoder, bool reset_menu_state, const bool feedback=false);

#define MENU_BEGIN() menu_start(); for(menu_row = 0; menu_row < LCD_HEIGHT; menu_row++, menu_line++) { menu_item = 0;
void menu_start(void);

#define MENU_END() menu_end(); }
extern void menu_end(void);

extern void menu_back(void);
extern void menu_back_no_reset(void);
extern void menu_back(uint8_t nLevel);

extern void menu_back_if_clicked(void);

extern void menu_submenu(menu_func_t submenu, const bool feedback=false);
extern void menu_submenu_no_reset(menu_func_t submenu, const bool feedback=false);

extern void menu_item_ret(void);

//extern int menu_draw_item_printf_P(char type_char, const char* format, ...);


//int menu_draw_item_puts_P_int16(char type_char, const char* str, int16_t val, );

#define MENU_ITEM_DUMMY() menu_item_dummy()
extern void menu_item_dummy(void);

#define MENU_ITEM_TEXT_P(str) do { menu_item_text_P(str); } while (0)
extern uint8_t menu_item_text_P(const char* str);

#define MENU_ITEM_SUBMENU_P(str, submenu) do { menu_item_submenu_P(str, submenu); } while (0)
extern void menu_item_submenu_P(const char* str, menu_func_t submenu);

#define MENU_ITEM_SUBMENU_E(sheet, submenu) do { menu_item_submenu_E(sheet, submenu); } while (0)
extern void menu_item_submenu_E(const Sheet &sheet, menu_func_t submenu);

#define MENU_ITEM_FUNCTION_E(sheet, submenu) do { menu_item_function_E(sheet, submenu); } while (0)
extern void menu_item_function_E(const Sheet &sheet, menu_func_t func);

#define MENU_ITEM_BACK_P(str) do { menu_item_back_P(str); } while (0)
extern void menu_item_back_P(const char* str);

// leaving menu - this condition must be immediately before MENU_ITEM_BACK_P
#define ON_MENU_LEAVE(func) do { if (menu_item_leave()){ func } } while (0)
extern bool menu_item_leave();

#define MENU_ITEM_FUNCTION_P(str, func) do { menu_item_function_P(str, func); } while (0)
extern void menu_item_function_P(const char* str, menu_func_t func);

#define MENU_ITEM_FUNCTION_NR_P(str, number, func, fn_par) do { menu_item_function_P(str, number, func, fn_par); } while (0)
extern void menu_item_function_P(const char* str, char number, void (*func)(uint8_t), uint8_t fn_par);

#define MENU_ITEM_TOGGLE_P(str, toggle, func) do { menu_item_toggle_P(str, toggle, func, 0x02); } while (0)
#define MENU_ITEM_TOGGLE(str, toggle, func) do { menu_item_toggle_P(str, toggle, func, 0x00); } while (0)
extern void menu_item_toggle_P(const char* str, const char* toggle, menu_func_t func, const uint8_t settings);

#define MENU_ITEM_GCODE_P(str, str_gcode) do { menu_item_gcode_P(str, str_gcode); } while (0)
extern void menu_item_gcode_P(const char* str, const char* str_gcode);


extern const char menu_fmt_int3[];

extern const char menu_fmt_float31[];
extern const char menu_fmt_float13[];

extern void menu_draw_float31(const char* str, float val);

extern void menu_draw_float13(const char* str, float val);

struct SheetFormatBuffer
{
    char c[19];
};

extern void menu_format_sheet_E(const Sheet &sheet_E, SheetFormatBuffer &buffer);


#define MENU_ITEM_EDIT_int3_P(str, pval, minval, maxval) do { menu_item_edit_P(str, pval, minval, maxval); } while (0)
//#define MENU_ITEM_EDIT_int3_P(str, pval, minval, maxval) MENU_ITEM_EDIT(int3, str, pval, minval, maxval)
template <typename T>
extern void menu_item_edit_P(const char* str, T pval, int16_t min_val, int16_t max_val);

extern void menu_progressbar_init(uint16_t total, const char* title);
extern void menu_progressbar_update(uint16_t newVal);
extern void menu_progressbar_finish(void);

#endif //_MENU_H
