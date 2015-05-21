/*
	The MIT License(MIT)

	Copyright(c) 2015 Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <vix_vector3.h>

namespace Vixen {

	const Vector3 Vector3::Zero(0, 0, 0);
	const Vector3 Vector3::One(1, 1, 1);
	const Vector3 Vector3::UnitX(1, 0, 0);
	const Vector3 Vector3::UnitY(0, 1, 0);
	const Vector3 Vector3::UnitZ(0, 0, 1);
	const Vector3 Vector3::Forward(0, 0, 1);
	const Vector3 Vector3::Backward(0, 0, -1);
	const Vector3 Vector3::Up(0, 1, 0);
	const Vector3 Vector3::Down(0, -1, 0);
	const Vector3 Vector3::Left(-1, 0, 0);
	const Vector3 Vector3::Right(1, 0, 0);
}
