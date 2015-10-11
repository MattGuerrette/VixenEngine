/*
	Copyright (C) 2015  Matt Guerrette

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
