#pragma once
#ifndef _PHOTOXEL_KEY_CODE_H_
#define _PHOTOXEL_KEY_CODE_H_

#include <inttypes.h>

namespace Photoxel
{
	enum class KeyCode : uint8_t
	{
		None = 0x00,
		LButton = 0x01,
		RButton = 0x02,
		Cancel = 0x03,
		MButton = 0x04,
		XButton1 = 0x05,
		XButton2 = 0x06,
		// 0x07 Empty
		Back = 0x08,
		Tab = 0x09,
		// 0x0A and 0x0B Reserved 
		Clear = 0x0C,
		Return = 0x0D,
		// 0x0E and 0x0F Undefined
		Shift = 0x10,
		Control = 0x11,
		Menu = 0x12,
		Pause = 0x13,
		Capital = 0x14, CapsLock = 0x14,
		Kana = 0x15, Hanguel = 0x15, Hangul = 0x15,
		ImeOn = 0x16,
		Junja = 0x17,
		Final = 0x18,
		Hanja = 0x19, Kanji = 0x19,
		ImeOff = 0x1A,
		Escape = 0x1B,
		Convert = 0x1C,
		NonConvert = 0x1D,
		Accept = 0x1E,
		ModeChange = 0x1F,

		Space = 0x20,
		Prior = 0x21, PageUp = 0x21,
		Next = 0x22, PageDown = 0x22,
		End = 0x23,
		Home = 0x24,
		Left = 0x25,
		Up = 0x26,
		Right = 0x27,
		Down = 0x28,
		Select = 0x29,
		Print = 0x2A,
		Execute = 0x2B,
		Snapshot = 0x2C, PrintScreen = 0x2C,
		Insert = 0x2D,
		Delete = 0x2E,
		Help = 0x2F,

		_0 = '0', _1 = '1', _2 = '2', _3 = '3', _4 = '4',
		_5 = '5', _6 = '6', _7 = '7', _8 = '8', _9 = '9',

		A = 'A', B = 'B', C = 'C', D = 'D', E = 'E',
		F = 'F', G = 'G', H = 'H', I = 'I', J = 'J',
		K = 'K', L = 'L', M = 'M', N = 'N', O = 'O',
		P = 'P', Q = 'Q', R = 'R', S = 'S', T = 'T',
		U = 'U', V = 'V', W = 'W', X = 'X', Y = 'Y',
		Z = 'Z',

		NumPad0 = 0x60, NumPad1 = 0x61, NumPad2 = 0x62, NumPad3 = 0x63, NumPad4 = 0x64,
		NumPad5 = 0x65, NumPad6 = 0x66, NumPad7 = 0x67, NumPad8 = 0x68, NumPad9 = 0x69,

		Multiply = 0x6A,
		Add = 0x6B,
		Separator = 0x6C,
		Substract = 0x6D,
		Decimal = 0x6E,
		Divide = 0x6F,

		F1 = 0x70, F2 = 0x71, F3 = 0x72, F4 = 0x73, F5 = 0x74, 
		F6 = 0x75, F7 = 0x76, F8 = 0x77, F9 = 0x78, F10 = 0x79,
		F11 = 0x7A, F12 = 0x7B, F13 = 0x7C, F14 = 0x7D, F15 = 0x7E,
		F16 = 0x7F, F17 = 0x80, F18 = 0x81, F19 = 0x82, F20 = 0x83,
		F21 = 0x84, F22 = 0x85, F23 = 0x86, F24 = 0x87 

	};
}

#endif
