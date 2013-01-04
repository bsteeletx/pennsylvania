#include "MyOptions.h"
#include "MyMenu.h"
#include "Globals.h"
#include "agk.h"

MyOptions::MyOptions(void)
{
	
}


MyOptions::~MyOptions(void)
{
}

void MyOptions::setup(AnimatedSprite *Symbol)
{
    int imgNum;
    
    Parent.setImage("default/Options.png");
    
	///step 1: setup or setData/////////////
	/*NewGame.setup(Symbol, "new_game", Parent);
	ResumeGame.setup(Symbol, "resume", Parent);*/
    
    imgNum = Parent.getImageNumber("options_background.png");
	Background.setImageNumber(imgNum);
    
    imgNum = Parent.getImageNumber("background_g.jpg");
	ThemeOption[0].setImageNumber(imgNum);
    
    imgNum = Parent.getImageNumber("background_r.jpg");
	ThemeOption[1].setImageNumber(imgNum);
    
    imgNum = Parent.getImageNumber("background_a.jpg");
	ThemeOption[2].setImageNumber(imgNum);
	//ThemeOption[3].setData(pImage, "background_f.jpg");
	//ThemeOption[4].setData(pImage, "background_e.jpg");
	//ThemeOption[5].setData(pImage, "background_w.jpg");
	/*SoundCheck.setData("sound_btn", Parent);
	Left.setup(Symbol, "left_arrow", Parent);
	Right.setup(Symbol, "right_arrow", Parent);*/
	
	Symbol->incrementSpriteFrame();
	agk::Sync();

	///step 2: setSize
	Background.setSize(100.0f);
    
    /*if (PLATFORM == TABLET)
    {
        SoundCheck.Checked.setSize(45.0f);
        SoundCheck.NotChecked.setSize(45.0f);
    }
    else
    {
        SoundCheck.Checked.setSize(37.5f);
        SoundCheck.NotChecked.setSize(37.5f);
    }*/

	for (short int i = 0; i < 3; i++)
		ThemeOption[i].setSize(45.0f);

	/*NewGame.setSize(20.0f);
	ResumeGame.setSize(20.0f);

	Left.setSize(10.0f);
	Right.setSize(10.0f);*/
		
	Symbol->incrementSpriteFrame();
	agk::Sync();

	///step 3: set priority
	setPriority(100);

	Symbol->incrementSpriteFrame();
	agk::Sync();
	
	///step 4: set x, y location with display
    Background.display(0.0f, 0.0f);
	/*Left.display(WEST_LOC_X, 39.0f);
	Right.display(EAST_LOC_X, 39.0f);*/

	/*for (short int i = 0; i < NUM_TABLE_TOP; i++)
		ThemeOption[i].display(27.5f, 23.0f);*/

	Symbol->incrementSpriteFrame();
	agk::Sync();

	///step 5: hide
	hide();

	Symbol->incrementSpriteFrame();
	agk::Sync();

	///step 6 (optional): set imprint


}

void MyOptions::show(short int curStyle)
{
	Background.show();

	ThemeOption[curStyle].show();
	
	/*if (isMuted)
		SoundCheck.NotChecked.show();
	else
		SoundCheck.Checked.show();

	NewGame.ButtonUp.show();
	ResumeGame.ButtonUp.show();

	Left.show();
	Right.show();
	//MainMenu.ButtonUp.show();*/
}

bool MyOptions::arrowAnimation(short stage, short button)
{
	bool val = false;

	/*switch(button)
	{
	case 5:
		val = Right.animation(stage);
		break;
	case 6:
		val = Left.animation(stage);
		break;
	}*/

	return val;
}

void MyOptions::mute(void)
{
	if (isMuted)
		return;

	isMuted = true;
	//SoundCheck.NotChecked.show();
	//SoundCheck.Checked.hide();
	muteSound();
}

void MyOptions::unMute(void)
{
	if (!isMuted)
		return;

	isMuted = false;
//	SoundCheck.Checked.show();
//	SoundCheck.NotChecked.hide();
	unMuteSound();
}

void MyOptions::setPriority(short unsigned int value)
{
	for (short int i = 0; i < 6; i++)
		ThemeOption[i].setPriority(value + 1);

	Background.setPriority(1);

/*	SoundCheck.Checked.setPriority(value + 1);
	SoundCheck.NotChecked.setPriority(value + 1);

	NewGame.setPriority(value + 2);
	ResumeGame.setPriority(value + 2);

	Left.setPriority(value + 1);
	Right.setPriority(value + 1);*/
}

void MyOptions::update()
{
	short int choice = 0;
		
	float mouseX = agk::GetPointerX();
	float mouseY = agk::GetPointerY();

/*	if (isMuted && SoundCheck.Checked.isVisible())
	{
		SoundCheck.Checked.hide();
		SoundCheck.NotChecked.show();
	}
	else if (!isMuted && SoundCheck.NotChecked.isVisible())
	{
		SoundCheck.Checked.show();
		SoundCheck.NotChecked.hide();
	}*/

	if ((mouseX >= 40.0f) && (mouseX <= 60.0f))
	{
		if((mouseY >= 83.0f) && (mouseY <= 94.0f))
			choice = 1;
	}

	/*if (ResumeGame.ButtonUp.isVisible())
	{
		if ((mouseX >= 65.0f) && (mouseX <= 85.0f))
		{
			if ((mouseY >= 80.0f) && (mouseY <= 92.0f))
				choice = 2;
		} 
	}

	if (choice == 0)
	{
		NewGame.ButtonOver.hide();
		ResumeGame.ButtonOver.hide();
		return;
	}
	else if (choice == 1)
	{
		NewGame.ButtonOver.show();
		ResumeGame.ButtonOver.hide();
	}
	else if (choice == 2)
	{
		ResumeGame.ButtonOver.show();
		NewGame.ButtonOver.hide();
	}*/
}	 

/*void MyOptions::hide()
{
	NewGame.hide();
	ResumeGame.hide();
	//Background.hide();
}*/