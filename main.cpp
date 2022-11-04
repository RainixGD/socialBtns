#include "win32cac.h"
#include <cocos2d.h>
#include <array>
#include <string>
#include <iostream>
#include <fstream>
#include <cJSON.h>
#include <cJSON.c>


//all information about buttons
struct {
	std::array<std::string, 7> links;
	std::array<std::string, 7> textures;
	std::array<bool, 7> isActive;
}BtnsOptions;

CCPoint btnPos[7] = { ccp(NULL, NULL), ccp(-30, 30), ccp(0, 30), ccp(30, 30), ccp(-30, 0), ccp(0, 0), ccp(30, 0) };//X and Y array for new buttons


class SocialBtns {
public:

	//buttons callbacks
	void onClick(CCObject* obj) {
		CCApplication::sharedApplication()->openURL(BtnsOptions.links[obj->getTag() - 100].c_str());
	}

	//init function
	__declspec(dllexport) static void init(CCNode* self) {
		//trying to find file with options
		std::ifstream file("Resources/socialBtns.json");
		if (file) {
			int n = 2048; char* buffer = new char[n + 1]; buffer[n] = 0; //buffer for JSON "text"
			file.read(buffer, n); //reading file
			cJSON* monitor_json = cJSON_Parse(buffer); //parsing file to "cJSON" object

			for (int i = 1; i < 7; i++) { //puting all values from JSON to options structure
				BtnsOptions.isActive[i] = cJSON_GetObjectItemCaseSensitive(monitor_json, ("isActive" + std::to_string(i)).c_str())->valueint;
				BtnsOptions.textures[i] = cJSON_GetObjectItemCaseSensitive(monitor_json, ("texture" + std::to_string(i)).c_str())->valuestring;
				BtnsOptions.links[i] = cJSON_GetObjectItemCaseSensitive(monitor_json, ("link" + std::to_string(i)).c_str())->valuestring;
			}


			int childrenCount = self->getChildrenCount();
			for (int i = 0; i < childrenCount; i++) {//trying to find CCMenu, where are RobTop's social buttons
				int x = (dynamic_cast<CCNode*>(self->getChildren()->objectAtIndex(i)))->getPositionX();
				int y = (dynamic_cast<CCNode*>(self->getChildren()->objectAtIndex(i)))->getPositionY();
				auto obj = dynamic_cast<CCNode*>(self->getChildren()->objectAtIndex(i));

				if ((obj->getPosition().x >= 50 && obj->getPosition().x <= 51) && (obj->getPosition().y >= 24 && obj->getPosition().y <= 25)) {
					
					obj->removeAllChildren();//removing all RobTop's buttons
					int errorLabelPosY = CCDirector::sharedDirector()->getWinSize().height; //Y position for error label

					for (int i = 1; i < 7; i++) {//creating new buttons!
						if (!BtnsOptions.isActive[i])//checking is button exist
							continue;

						auto btnSprite = CCSprite::create(BtnsOptions.textures[i].c_str()); //creating sprite for button

						if (btnSprite == NULL) {// if no texture:
							btnSprite = CCSprite::createWithSpriteFrameName("GJ_deleteIcon_001.png");
							auto errorLabel = CCLabelBMFont::create(("Texture " + BtnsOptions.textures[i] + " NOT found!").c_str(), "bigFont.fnt");//error label
							errorLabel->setColor({ 255, 0, 0 });
							errorLabel->setAnchorPoint({ 0, 0.5 });
							errorLabel->setScale(0.2);
							errorLabel->setPosition({ 0, float(errorLabelPosY-=5) });
							self->addChild(errorLabel, 10);
						}

						btnSprite->setScale(0.8);
						auto btn = CCMenuItemSpriteExtra::create(btnSprite, obj, menu_selector(SocialBtns::onClick));//creating button
						btn->setPosition(btnPos[i]);
						obj->addChild(btn, 5, 100 + i);
					}

				}
			}
		}
		else {//problems with JSON
			auto errorLabel = CCLabelBMFont::create("Problems with 'socialBtns.json'", "bigFont.fnt");
			errorLabel->setColor({ 255, 0, 0 });
			errorLabel->setScale(0.6);
			errorLabel->setPosition({ CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height - 10 });
			self->addChild(errorLabel);
		}
	}
};