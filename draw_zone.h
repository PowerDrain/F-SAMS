#include "displays.h"
#include  "globaltypes.h"
void drawZone(int zoneId, int alarmtype){

	switch (zoneId){
	case 1:
            if(alarmtype==1){
                glutDisplayFunc(drawFireZone1);
                }else{
                glutDisplayFunc(drawSecZone1);
            }
	    break;
	case 2:
            if(alarmtype==1){
                glutDisplayFunc(drawFireZone2);
		//glutDisplayFunc(DisplayExit);
            }else{
                glutDisplayFunc(drawSecZone2);
            }
	    break;
	case 3:
            if(alarmtype==1){
                glutDisplayFunc(drawFireZone3);
		//glutDisplayFunc(DisplayExit);
		}else{
                glutDisplayFunc(drawSecZone3);
            }
	    break;
	case 4:
            if(alarmtype==1){
                glutDisplayFunc(drawFireZone4);
		//glutDisplayFunc(DisplayExit);//#include  "globaltypes.h"
            }else{
                glutDisplayFunc(drawSecZone4);
            }
	    break;
	case 5:
            if(alarmtype==1){
                glutDisplayFunc(drawFireZone5);
		//glutDisplayFunc(DisplayExit);
            }else{
                glutDisplayFunc(drawSecZone5);
            }
	    break;
	case 6:
            if(alarmtype==1){
                glutDisplayFunc(drawFireZone6);
		//glutDisplayFunc(DisplayExit);
            }else{
                glutDisplayFunc(drawSecZone6);
            }
	    break;
	case 7:
            if(alarmtype==1){
                glutDisplayFunc(drawFireZone7);
		//glutDisplayFunc(DisplayExit);
            }
            else{
                glutDisplayFunc(drawSecZone7);
            }
	    break;
	case 8:
            if(alarmtype==1){
                glutDisplayFunc(drawFireZone8);
		//glutDisplayFunc(DisplayExit);
            }else{
                glutDisplayFunc(drawSecZone8);
            }
	    break;
	default:
		break;
	}
}