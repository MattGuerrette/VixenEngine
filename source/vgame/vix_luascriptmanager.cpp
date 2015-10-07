/*
	The MIT License(MIT)

	Copyright(c) 2015 Vixen Team, Matt Guerrette

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


#include <vix_luascriptmanager.h>
#include <vix_luaengine.h>
#include <vix_pathmanager.h>
#include <vix_filemanager.h>
#include <vix_platform.h>
#include <vix_transform.h>
#include <vix_model.h>
#include <vix_camera3d.h>
#include <vix_component.h>
#include <vix_containers.h>
#include <vix_debugutil.h>
#include <vix_gameobject.h>
#include <vix_input.h>
#include <vix_scenemanager.h>
#include <vix_prefabmanager.h>

namespace Vixen {

	LuaIntf::LuaRef* LuaScriptManager::s_thisTable = NULL;
	std::stack<LuaScript*> LuaScriptManager::m_scriptStack;

	void LuaScriptManager::Initialize()
	{
		using namespace LuaIntf;

		LuaBinding(LuaEngine::L())
			.beginModule("this")
			.endModule();

		s_thisTable = new LuaRef(LuaEngine::L(), "this");

		BindLuaObjects();
	}

	LuaScript* LuaScriptManager::PeekScript()
	{
		if (LuaScriptManager::m_scriptStack.size() > 0)
			return &*LuaScriptManager::m_scriptStack.top();
		else
			return NULL;
	}

	void LuaScriptManager::PopScript()
	{
		if (LuaScriptManager::m_scriptStack.size() > 0)
			LuaScriptManager::m_scriptStack.pop();
	}
	
	void LuaScriptManager::PushScript(LuaScript* script)
	{
		LuaScriptManager::m_scriptStack.push(script);
	}

	LuaScript* LuaScriptManager::LoadScript(UString name)
    {

		using namespace LuaIntf;

        UString _assetPath = PathManager::ScriptPath() + name;

        File* file = FileManager::OpenFile(_assetPath);
        if (file)
        {
            //std::string _fileName = UStringToStd(file->BaseName() + VTEXT(".Update"));
			std::string _filename = UStringToStd(file->BaseName());

            //now I want to load the actual script object
            
			LuaBinding(LuaEngine::L())
				.beginModule(_filename.c_str())
					.beginModule("hash")
					.endModule()
				.endModule();
			

		    LuaEngine::ExecuteFile(_assetPath);

            
			LuaIntf::LuaRef* onInit = new LuaRef(LuaEngine::L(), (_filename + ".OnInit").c_str());
			LuaIntf::LuaRef* onEnable = new LuaRef(LuaEngine::L(), (_filename + ".OnEnable").c_str());
            LuaIntf::LuaRef* update = new LuaRef(LuaEngine::L(), (_filename + ".Update").c_str());
			LuaIntf::LuaRef* onDisable = new LuaRef(LuaEngine::L(), (_filename + ".OnDisable").c_str());
			LuaIntf::LuaRef* onDestroy = new LuaRef(LuaEngine::L(), (_filename + ".OnDestroy").c_str());

            LuaScript* _script = new LuaScript;

			_script->BindOnInitFunction(onInit);
			_script->BindOnEnableFunction(onEnable);
            _script->BindUpdateFunction(update);
			_script->BindOnDisableFunction(onDisable);
			_script->BindOnDestroyFunction(onDestroy);

            _script->SetID(file->BaseName());

            FileManager::CloseFile(file);
            return _script;
            
        }
       
    
        return NULL;
    }


	void LuaScriptManager::BindLuaObjects()
	{
		using namespace LuaIntf;

		

		////////////////////////////////////////////////////////////////////////////////////
		/* Vector3                                                                        */
		////////////////////////////////////////////////////////////////////////////////////
		LuaBinding(LuaEngine::L())
			.beginClass<Vector3>("Vector3")
			.addConstructor(LUA_ARGS(_opt<float>, _opt<float>, _opt<float>))
			.addFunction("Length", &Vector3::Length)
			.addFunction("LengthSquared", &Vector3::LengthSquared)
			.addFunction("Distance", &Vector3::Distance, LUA_ARGS(_opt<Vector3>))
			.addFunction("Dot", &Vector3::Dot, LUA_ARGS(_opt<Vector3>))
			.addFunction("Normalize", &Vector3::Normalize)
			.addFunction("normalise", &Vector3::normalise)
			.addFunction("Angle", &Vector3::Angle, LUA_ARGS(_opt<Vector3>))
			.addFunction("Cross", &Vector3::Cross, LUA_ARGS(_opt<Vector3>))
			.addFunction("X", &Vector3::X)
			.addFunction("Y", &Vector3::Y)
			.addFunction("Z", &Vector3::Z)
            .addFunction("__add", &Vector3::add)
            .addFunction("__sub", &Vector3::sub)
            .addFunction("__mul", &Vector3::mul)
            .addFunction("ToString", &Vector3::ToStdString)
			.endClass();


		////////////////////////////////////////////////////////////////////////////////////
		/* Transform                                                                      */
		////////////////////////////////////////////////////////////////////////////////////
		LuaBinding(LuaEngine::L())
			.beginClass<Transform>("Transform")
			.addConstructor(LUA_ARGS(_opt<float>, _opt<float>, _opt<float>, _opt<float>, _opt<float>, _opt<float>, _opt<float>, _opt<float>, _opt<float>))
			.addFunction("RotateX", &Transform::RotateX, LUA_ARGS(_opt<float>))
			.addFunction("RotateY", &Transform::RotateY, LUA_ARGS(_opt<float>))
			.addFunction("RotateZ", &Transform::RotateZ, LUA_ARGS(_opt<float>))
			.addFunction("TranslateX", &Transform::TranslateX, LUA_ARGS(float))
			.addFunction("TranslateY", &Transform::TranslateY, LUA_ARGS(float))
			.addFunction("TranslateZ", &Transform::TranslateZ, LUA_ARGS(float))
			.addFunction("Translate", &Transform::Translate, LUA_ARGS(Vector3))
			.addProperty("Position", &Transform::GetPosition, &Transform::SetPosition)
			.addProperty("Rotation", &Transform::GetRotation, &Transform::SetRotation)
			.addProperty("Scale", &Transform::GetScale, &Transform::SetScale)
			.addFunction("Forward", &Transform::GetForward)
			.addFunction("Up", &Transform::GetUp)
			.addFunction("Right", &Transform::GetRight)
			.addFunction("Print", &Transform::DebugPrint)
			.endClass();

		////////////////////////////////////////////////////////////////////////////////////
		/* GameObject                                                                     */
		////////////////////////////////////////////////////////////////////////////////////

		LuaBinding(LuaEngine::L())
			.beginClass<GameObject>("GameObject")
			.addFunction("SetEnabled", &GameObject::SetEnabled, LUA_ARGS(_opt<bool>, _opt<bool>))
			.addFunction("GetChild", &GameObject::GetChild, LUA_ARGS(_opt<int>))
			.addFunction("GetTransform", &GameObject::GetTransformRef)
			.addFunction("GetName", &GameObject::GetName)
			.addFunction("GetID", &GameObject::GetID)
			.addFunction("Delete", &GameObject::Delete)
			.endClass();

		////////////////////////////////////////////////////////////////////////////////////
		/* Prefab                                                                         */
		////////////////////////////////////////////////////////////////////////////////////

		LuaBinding(LuaEngine::L())
			.beginClass<Prefab>("Prefab")
			.addFunction("CreateObject", &Prefab::CreateObject)
			.addFunction("MarkStore", &Prefab::IncRefCount)
			.addFunction("MarkDelete", &Prefab::DecRefCount)
			.endClass();


		////////////////////////////////////////////////////////////////////////////////////
		/* Input Bindings                                                                 */
		////////////////////////////////////////////////////////////////////////////////////

		LuaBinding(LuaEngine::L())
			.beginModule("Input")
			.addFunction("KeyPress", &Input::KeyPress)
			.addFunction("SingleKeyPress", &Input::SingleKeyPress)
			.addFunction("KeyRelease", &Input::KeyRelease)
			.addFunction("ButtonPress", &Input::ButtonPress)
			.addFunction("SingleButtonPress", &Input::SingleButtonPress)
			.addFunction("ButtonRelease", &Input::ButtonRelease)
			.addFunction("MouseX", &Input::MouseX)
			.addFunction("MouseY", &Input::MouseY)
			.addFunction("MouseWheelX", &Input::MouseWheelX)
			.addFunction("MouseWheelY", &Input::MouseWheelY)
			.addFunction("MouseDeltaX", &Input::DeltaX)
			.addFunction("MouseDeltaY", &Input::DeltaY)
			.endModule();

        ////////////////////////////////////////////////////////////////////////////////////
        /* FileManager                                                                    */
        ////////////////////////////////////////////////////////////////////////////////////

		LuaBinding(LuaEngine::L())
			.beginModule("FileManager")
			.addFunction("PrintOpen", &FileManager::PrintOpen)
            .addFunction("TotalBytes", &FileManager::TotalBytesOpen)
			.endModule();


		////////////////////////////////////////////////////////////////////////////////////
		/* Keycodes                                                                    */
		////////////////////////////////////////////////////////////////////////////////////

		LuaBinding(LuaEngine::L())
			.beginModule("IKEY")
			.addConstant("A", IKEY::A)
			.addConstant("B", IKEY::B)
			.addConstant("C", IKEY::C)
			.addConstant("D", IKEY::D)
			.addConstant("E", IKEY::E)
			.addConstant("F", IKEY::F)
			.addConstant("G", IKEY::G)
			.addConstant("H", IKEY::H)
			.addConstant("I", IKEY::I)
			.addConstant("J", IKEY::J)
			.addConstant("K", IKEY::K)
			.addConstant("L", IKEY::L)
			.addConstant("M", IKEY::M)
			.addConstant("N", IKEY::N)
			.addConstant("O", IKEY::O)
			.addConstant("P", IKEY::P)
			.addConstant("Q", IKEY::Q)
			.addConstant("R", IKEY::R)
			.addConstant("S", IKEY::S)
			.addConstant("T", IKEY::T)
			.addConstant("U", IKEY::U)
			.addConstant("V", IKEY::V)
			.addConstant("W", IKEY::W)
			.addConstant("X", IKEY::X)
			.addConstant("Y", IKEY::Y)
			.addConstant("Z", IKEY::Z)
			.addConstant("0", IKEY::NUM0)
			.addConstant("1", IKEY::NUM1)
			.addConstant("2", IKEY::NUM2)
			.addConstant("3", IKEY::NUM3)
			.addConstant("4", IKEY::NUM4)
			.addConstant("5", IKEY::NUM5)
			.addConstant("6", IKEY::NUM6)
			.addConstant("7", IKEY::NUM7)
			.addConstant("8", IKEY::NUM8)
			.addConstant("9", IKEY::NUM9)
			.addConstant("F1", IKEY::F1)
			.addConstant("F2", IKEY::F2)
			.addConstant("F3", IKEY::F3)
			.addConstant("F4", IKEY::F4)
			.addConstant("F5", IKEY::F5)
			.addConstant("F6", IKEY::F6)
			.addConstant("F7", IKEY::F7)
			.addConstant("F8", IKEY::F8)
			.addConstant("F9", IKEY::F9)
			.addConstant("F10", IKEY::F10)
			.addConstant("F11", IKEY::F11)
			.addConstant("F12", IKEY::F12)
			.addConstant("UP", IKEY::UP)
			.addConstant("DOWN", IKEY::DOWN)
			.addConstant("LEFT", IKEY::LEFT)
			.addConstant("RIGHT", IKEY::RIGHT)
			.addConstant("SPACE", IKEY::SPACE)
			.endModule();

        LuaBinding(LuaEngine::L())
            .beginModule("Scene")
            .addFunction("FindObjectWithName", &SceneManager::AccessTopLevelObject, LUA_ARGS(std::string));

        LuaBinding(LuaEngine::L())
            .beginModule("Prefab")
            .addFunction("Load", &PrefabManager::Load, LUA_ARGS(_opt<std::string>));
            
	}
}