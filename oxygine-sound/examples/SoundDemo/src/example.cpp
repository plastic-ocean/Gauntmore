#include "oxygine-framework.h"

#include "core/STDFileSystem.h"

#include "test.h"
#include "TestSoundFormats.h"
#include "TestStress.h"
#ifdef __S3E__
#include "s3eKeyboard.h"
#endif


#include "SoundPlayer.h"
#include "SoundSystem.h"

using namespace oxygine;

spActor _tests;

//it is our resources
//in real project you would have more than one Resources declarations. It is important on mobile devices with limited memory and you would load/unload them
Resources resources;
Resources resourcesUI;
SoundPlayer splayer;

class TestActor: public Test
{
public:		

	TestActor()
	{	
		_tests = this;
		_x = RootActor::instance->getWidth()/2.0f;
		_y = 0;


		addButton("sound_formats", "sound formats");
		addButton("stress_test", "stress test");
		addButton("exit", "exit");	

		getRoot()->addEventListener(RootActor::ACTIVATE, CLOSURE(this, &TestActor::resume));
		getRoot()->addEventListener(RootActor::DEACTIVATE, CLOSURE(this, &TestActor::pause));
	}

	void pause(Event *)
	{
		SoundSystem::instance->pause();
	}

	void resume(Event *)
	{
		SoundSystem::instance->resume();
	}

	void clicked(string id)
	{
		setVisible(false);

		if (id == "sound_formats")
		{
			RootActor::instance->addChild(new TestSoundFormats);
		}
		
		if (id == "stress_test")
		{
			RootActor::instance->addChild(new TestStress);
		}

		if (id == "exit")
		{
			core::requestQuit();
		}
	}
};

file::STDFileSystem extfs(true);

void example_preinit()
{

}

void example_init()
{
	//mount additional file system with inner path "ext"
	//it would be used for searching path in data/ext
	extfs.setPath(file::fs().getFullPath("ext").c_str());
	file::mount(&extfs);

	//initialize our sound system with 16 channels
	
	SoundSystem::instance = SoundSystem::create();
	SoundSystem::instance->init(16);

	//initialize SoundPlayer
	SoundPlayer::initialize();
	splayer.setResources(&resources);

	//load xml file with resources definition
	resources.loadXML("xmls/res.xml");
	resourcesUI.loadXML("demo/res_ui.xml");
	resourcesUI.loadXML("demo/fonts.xml");

	spSprite sp = initActor(new Sprite, 
		arg_resAnim = resourcesUI.getResAnim("logo2"),
		arg_attachTo = getRoot(),
		arg_priority = 10,
		arg_alpha = 128
		);

	sp->setX(getRoot()->getWidth() - sp->getWidth());
	sp->setY(getRoot()->getHeight() - sp->getHeight());

	_tests = new TestActor;
	RootActor::instance->addChild(_tests);


	for (int i = 0; i < resources.getCount(); ++i)
	{
		ResSound *rs = dynamic_cast<ResSound*>(resources.get(i));
		if (!rs)
			continue;

#ifdef EMSCRIPTEN
		EM_ASM_ARGS({
			var p = Preloading("hello");
			p.add(Pointer_stringify($0));
			p.start();
		}, rs->getPath().c_str());
#endif
	}
}

void example_update()
{
	SoundSystem::instance->update();
	splayer.update();
}

void example_destroy()
{
	splayer.stop();
	SoundSystem::instance->stop();
	_tests->detach();
	_tests = 0;
	resources.free();
	resourcesUI.free();
	SoundSystem::instance->release();
}


