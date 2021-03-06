//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "Wrappers/GUI/BsScriptGUIProgressBar.h"
#include "BsScriptMeta.h"
#include "BsMonoField.h"
#include "BsMonoClass.h"
#include "BsMonoManager.h"
#include "BsMonoMethod.h"
#include "2D/BsSpriteTexture.h"
#include "BsMonoUtil.h"
#include "GUI/BsGUILayout.h"
#include "GUI/BsGUIProgressBar.h"
#include "GUI/BsGUIOptions.h"
#include "Wrappers/GUI/BsScriptGUIElementStyle.h"
#include "Wrappers/GUI/BsScriptGUILayout.h"
#include "Wrappers/BsScriptHString.h"
#include "Wrappers/GUI/BsScriptGUIContent.h"

using namespace std::placeholders;

namespace bs
{
	ScriptGUIProgressBar::ScriptGUIProgressBar(MonoObject* instance, GUIProgressBar* progressBar)
		:TScriptGUIElement(instance, progressBar)
	{

	}

	void ScriptGUIProgressBar::initRuntimeData()
	{
		metaData.scriptClass->addInternalCall("Internal_CreateInstance", (void*)&ScriptGUIProgressBar::internal_createInstance);
		metaData.scriptClass->addInternalCall("Internal_SetPercent", (void*)&ScriptGUIProgressBar::internal_setPercent);
		metaData.scriptClass->addInternalCall("Internal_GetPercent", (void*)&ScriptGUIProgressBar::internal_getPercent);
		metaData.scriptClass->addInternalCall("Internal_SetTint", (void*)&ScriptGUIProgressBar::internal_setTint);
	}

	void ScriptGUIProgressBar::internal_createInstance(MonoObject* instance, MonoString* style, MonoArray* guiOptions)
	{
		GUIOptions options;

		ScriptArray scriptArray(guiOptions);
		UINT32 arrayLen = scriptArray.size();
		for (UINT32 i = 0; i < arrayLen; i++)
			options.addOption(scriptArray.get<GUIOption>(i));

		GUIProgressBar* progressBar = GUIProgressBar::create(options, toString(MonoUtil::monoToWString(style)));
		new (bs_alloc<ScriptGUIProgressBar>()) ScriptGUIProgressBar(instance, progressBar);
	}

	void ScriptGUIProgressBar::internal_setPercent(ScriptGUIProgressBar* nativeInstance, float percent)
	{
		GUIProgressBar* progressBar = (GUIProgressBar*)nativeInstance->getGUIElement();
		progressBar->setPercent(percent);
	}

	float ScriptGUIProgressBar::internal_getPercent(ScriptGUIProgressBar* nativeInstance)
	{
		GUIProgressBar* progressBar = (GUIProgressBar*)nativeInstance->getGUIElement();
		return progressBar->getPercent();
	}

	void ScriptGUIProgressBar::internal_setTint(ScriptGUIProgressBar* nativeInstance, Color* color)
	{
		GUIProgressBar* progressBar = (GUIProgressBar*)nativeInstance->getGUIElement();
		progressBar->setTint(*color);
	}
}