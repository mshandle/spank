LIBSPANK_SOURCE_FILES := \
		$(LIBSPANK_SOURCE)/action/ActionBackMoveTo.cpp \
		$(LIBSPANK_SOURCE)/action/ActionBounceMoveTo.cpp \
		$(LIBSPANK_SOURCE)/action/ActionBySpline.cpp \
		$(LIBSPANK_SOURCE)/action/ActionCircMoveTo.cpp \
		$(LIBSPANK_SOURCE)/action/ActionCompose.cpp \
		$(LIBSPANK_SOURCE)/action/ActionCubicBSpline.cpp \
		$(LIBSPANK_SOURCE)/action/ActionCubicMoveTo.cpp \
		$(LIBSPANK_SOURCE)/action/ActionDelay.cpp \
		$(LIBSPANK_SOURCE)/action/ActionElasticMoveTo.cpp \
		$(LIBSPANK_SOURCE)/action/ActionExpoMoveTo.cpp \
		$(LIBSPANK_SOURCE)/action/ActionLoop.cpp \
		$(LIBSPANK_SOURCE)/action/ActionMoveBy.cpp \
		$(LIBSPANK_SOURCE)/action/ActionMoveTo.cpp \
		$(LIBSPANK_SOURCE)/action/ActionQuadMoveTo.cpp \
		$(LIBSPANK_SOURCE)/action/ActionQuartMoveTo.cpp \
		$(LIBSPANK_SOURCE)/action/ActionQuintMoveTo.cpp \
		$(LIBSPANK_SOURCE)/action/ActionRotateBy.cpp \
		$(LIBSPANK_SOURCE)/action/ActionRotateTo.cpp \
		$(LIBSPANK_SOURCE)/action/ActionScaleBy.cpp \
		$(LIBSPANK_SOURCE)/action/ActionScaleTo.cpp \
		$(LIBSPANK_SOURCE)/action/ActionSequeue.cpp \
		$(LIBSPANK_SOURCE)/action/ActionSineMoveTo.cpp \
		$(LIBSPANK_SOURCE)/action/IActionBase.cpp \
		$(LIBSPANK_SOURCE)/math/IMath.cpp \
		$(LIBSPANK_SOURCE)/math/Matrix2x2.cpp \
		$(LIBSPANK_SOURCE)/math/Matrix3x3.cpp \
		$(LIBSPANK_SOURCE)/math/Matrix4x4.cpp \
		$(LIBSPANK_SOURCE)/math/Quaternion.cpp \
		$(LIBSPANK_SOURCE)/math/Vector2.cpp \
		$(LIBSPANK_SOURCE)/math/Vector3.cpp \
		$(LIBSPANK_SOURCE)/math/Vector4.cpp \
		$(LIBSPANK_SOURCE)/msg/IMsgBase.cpp \
		$(LIBSPANK_SOURCE)/msg/IMsgHandler.cpp \
		$(LIBSPANK_SOURCE)/msg/MsgActionUpdate.cpp \
		$(LIBSPANK_SOURCE)/msg/MsgCommon.cpp \
		$(LIBSPANK_SOURCE)/msg/MsgMgr.cpp \
		$(LIBSPANK_SOURCE)/msg/MsgTouch.cpp \
		$(LIBSPANK_SOURCE)/particle/IEmmiter.cpp \
		$(LIBSPANK_SOURCE)/particle/IParticle.cpp \
		$(LIBSPANK_SOURCE)/particle/IParticleSystem.cpp \
		$(LIBSPANK_SOURCE)/particle/SnowEmmiter.cpp \
		$(LIBSPANK_SOURCE)/particle/SnowParticle.cpp \
		$(LIBSPANK_SOURCE)/particle/SnowParticleSystem.cpp \
		$(LIBSPANK_SOURCE)/platforms/android/Mutex_Android_Impl.cpp \
		$(LIBSPANK_SOURCE)/platforms/android/RenderDevice_Android_Impl.cpp \
		$(LIBSPANK_SOURCE)/platforms/android/util/DebugUtil_Android_Impl.cpp \
		$(LIBSPANK_SOURCE)/platforms/android/util/FileUtil_Android_Impl.cpp \
		$(LIBSPANK_SOURCE)/platforms/android/unzip/unzip.cpp \
		$(LIBSPANK_SOURCE)/platforms/android/unzip/ioapi.cpp \
		$(LIBSPANK_SOURCE)/ui/uimsg/IMsgBaseUI.cpp \
		$(LIBSPANK_SOURCE)/ui/uimsg/MsgCheck.cpp \
		$(LIBSPANK_SOURCE)/ui/uimsg/MsgClick.cpp \
		$(LIBSPANK_SOURCE)/ui/uimsg/MsgSlider.cpp \
		$(LIBSPANK_SOURCE)/ui/BitmapFont_Impl.cpp \
		$(LIBSPANK_SOURCE)/ui/RendererUI_Impl.cpp \
		$(LIBSPANK_SOURCE)/ui/RenderParam.cpp \
		$(LIBSPANK_SOURCE)/ui/UIButton.cpp \
		$(LIBSPANK_SOURCE)/ui/UICheckButton.cpp \
		$(LIBSPANK_SOURCE)/ui/UIRadioButton.cpp \
		$(LIBSPANK_SOURCE)/ui/UIResMgr_Impl.cpp \
		$(LIBSPANK_SOURCE)/ui/UIScreen.cpp \
		$(LIBSPANK_SOURCE)/ui/UISliderBar.cpp \
		$(LIBSPANK_SOURCE)/ui/UIString.cpp \
		$(LIBSPANK_SOURCE)/ui/UISystem_Impl.cpp \
		$(LIBSPANK_SOURCE)/ui/UITextView.cpp \
		$(LIBSPANK_SOURCE)/ui/UIWindow.cpp \
		$(LIBSPANK_SOURCE)/ui/UpdateParam.cpp \
		$(LIBSPANK_SOURCE)/ui/VertexCache.cpp \
		$(LIBSPANK_SOURCE)/util/ConfigUtil.cpp \
		$(LIBSPANK_SOURCE)/util/ScreenUtil.cpp \
		$(LIBSPANK_SOURCE)/util/StringUtil.cpp \
		$(LIBSPANK_SOURCE)/Core_Impl.cpp \
		$(LIBSPANK_SOURCE)/Image.cpp \
		$(LIBSPANK_SOURCE)/InputMgr.cpp \
		$(LIBSPANK_SOURCE)/IObject.cpp \
		$(LIBSPANK_SOURCE)/IRtti.cpp \
		$(LIBSPANK_SOURCE)/Level2D.cpp \
		$(LIBSPANK_SOURCE)/Node_Impl.cpp \
		$(LIBSPANK_SOURCE)/Renderer2D_Impl.cpp \
		$(LIBSPANK_SOURCE)/ResourceMgr_Impl.cpp \
		$(LIBSPANK_SOURCE)/Shader_Impl.cpp \
		$(LIBSPANK_SOURCE)/ShaderMgr_Impl.cpp \
		$(LIBSPANK_SOURCE)/Sprite.cpp \
		$(LIBSPANK_SOURCE)/StreamReader.cpp \
		$(LIBSPANK_SOURCE)/StreamWriter.cpp \
		$(LIBSPANK_SOURCE)/Texture_Impl.cpp \
		$(LIBSPANK_SOURCE)/TextureMgr_Impl.cpp \
		$(LIBSPANK_SOURCE)/VertexAttribute.cpp \
