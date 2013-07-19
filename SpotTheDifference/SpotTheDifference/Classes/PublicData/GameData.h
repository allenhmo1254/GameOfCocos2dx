//
//  GameData.h
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#ifndef SpotTheDifference_GameData_h
#define SpotTheDifference_GameData_h

#define SCREEN_WIDTH        CCDirector::sharedDirector() -> getWinSize().width
#define SCREEN_HEIGHT       CCDirector::sharedDirector() -> getWinSize().height

#define LevelSCENEMOVEOFFSET              50


typedef enum{
    DIR_NOMOVE = 0,
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
}FaceTo;


#endif
