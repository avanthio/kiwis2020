#include "screen_management.hpp"

//The code from here to line 142 is all for drawing buttons
bool autonSelected = false;//has an auton been chosen yet? (false)
int programRun = 0;//which auton gets run?

static lv_style_t my_red_style_pr;
static lv_style_t my_red_style_rel;
static lv_style_t my_blue_style_pr;
static lv_style_t my_blue_style_rel;
static lv_style_t my_autonsk_style_pr;
static lv_style_t my_autonsk_style_rel;
static lv_style_t my_pageflip_style_pr;
static lv_style_t my_pageflip_style_rel;
static lv_obj_t* pageADec;
static lv_obj_t* btnROne;
static lv_obj_t* labelROne;
static lv_obj_t* btnRTwo;
static lv_obj_t* labelRTwo;
static lv_obj_t* btnBOne;
static lv_obj_t* labelBOne;
static lv_obj_t* btnBTwo;
static lv_obj_t* labelBTwo;
static lv_obj_t* btnAS;
static lv_obj_t* labelAS;
static lv_obj_t* labelDec;
static lv_obj_t* btnPageFlipOne;
static lv_obj_t* labelPageFlipOne;
static lv_obj_t* btnPageFlipTwo;
static lv_obj_t* labelPageFlipTwo;

static int rowOne = 16;//first row of buttons
static int rowTwo = 16 + 112;//second row of buttons
static int rowOneFive = 64;//auton skills row
static int height = 100;//height of button
static int width = 140;//width of button


std::string stringROne = "Red Rectangle";
std::string stringRTwo = "Red Square";
std::string stringBOne = "Blue Square";
std::string stringBTwo = "Blue Rectangle";
std::string stringRThree = "Red 5pt";
std::string stringBThree = "Blue 5pt";


//this chooses the x value of the top corner of the button based on its number.
//(1-3 for both rows)

int calcButtonX(int buttonNumber) {
    int width = 140;//width of button
    int buttonSpacer = 15;//space between buttons
    int firstButtonStartX = 15;//start of first button
    return (buttonNumber - 1) * (width + buttonSpacer) + firstButtonStartX;
}

/* the callback for when a button is pressed. Uses the id (number assigned to button)
*  to select the auton run, and escape a while loop in competition_initialize()*/
static lv_res_t btn_press_action(lv_obj_t* btn) {
    int btnID=0;//id of each button
    if (LV_BTN_STATE_PR&&!autonSelected) {
        autonSelected = true;
        btnID=lv_obj_get_free_num(btn);
        programRun = btnID;
    }
    return LV_RES_OK;
}


static lv_res_t btn_press_action_alt(lv_obj_t* btn){
  int btnID = 0;
  if(LV_BTN_STATE_PR&&!autonSelected){
    btnID=lv_obj_get_free_num(btn);
    if(btnID == 6){
      pros::delay(1000);
      lv_obj_clean(lv_scr_act());
      create_buttons_pgTwo();
    }
    else if(btnID == 7){
      pros::delay(1000);
      lv_obj_clean(lv_scr_act());
      create_buttons();
    }
  }
  return LV_RES_OK;
}
// This function creates all the buttons for the auton selector
// and sets their style (gradients!!!!).
// It also sets the callback for when the buttons are pressed.

void create_buttons() {


	lv_style_copy(&my_red_style_pr, &lv_style_pretty_color);
	my_red_style_pr.body.main_color = lv_color_hex(0x910910);
	my_red_style_pr.body.grad_color = LV_COLOR_RED;


	lv_style_copy(&my_red_style_rel, &lv_style_pretty_color);
	my_red_style_rel.body.main_color = lv_color_hex(0x910910);
	my_red_style_rel.body.grad_color = lv_color_hex(0x96080f);


	lv_style_copy(&my_blue_style_pr, &lv_style_pretty_color);
	my_blue_style_pr.body.main_color = lv_color_hex(0x05057d);
	my_blue_style_pr.body.grad_color = LV_COLOR_BLUE;


	lv_style_copy(&my_blue_style_rel, &lv_style_pretty_color);
	my_blue_style_rel.body.main_color = lv_color_hex(0x05057d);
	my_blue_style_rel.body.grad_color = lv_color_hex(0x050566);

	lv_style_copy(&my_autonsk_style_pr, &lv_style_pretty_color);
	my_autonsk_style_pr.body.main_color = lv_color_hex(0x034f03);
	my_autonsk_style_pr.body.grad_color = lv_color_hex(0x1abd28);

	lv_style_copy(&my_autonsk_style_rel, &lv_style_pretty_color);
	my_autonsk_style_rel.body.main_color = lv_color_hex(0x034f03);
	my_autonsk_style_rel.body.grad_color = lv_color_hex(0x036e03);


  lv_style_copy(&my_pageflip_style_pr, &lv_style_pretty_color);
  my_pageflip_style_pr.body.main_color = lv_color_hex(0x502966);
  my_pageflip_style_pr.body.grad_color = lv_color_hex(0x310b47);

  lv_style_copy(&my_pageflip_style_rel, &lv_style_pretty_color);
  my_pageflip_style_rel.body.main_color = lv_color_hex(0x502966);
  my_pageflip_style_rel.body.grad_color = lv_color_hex(0x9b30d9);


  btnROne = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(btnROne,width, height);
  lv_obj_set_free_num(btnROne, 1);
  lv_btn_set_action(btnROne, LV_BTN_ACTION_PR, btn_press_action);
  lv_btn_set_style(btnROne, LV_BTN_STATE_REL, &my_red_style_pr);
  lv_btn_set_style(btnROne, LV_BTN_STATE_PR, &my_red_style_rel);
  lv_obj_set_pos(btnROne, calcButtonX(1), rowOne);

  labelROne = lv_label_create(btnROne, NULL);
  lv_label_set_text(labelROne, "Red Rectangle");

  btnRTwo = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(btnRTwo, width, height);
  lv_obj_set_free_num(btnRTwo, 2);
	lv_btn_set_action(btnRTwo, LV_BTN_ACTION_PR, btn_press_action);
  lv_btn_set_style(btnRTwo, LV_BTN_STATE_REL, &my_red_style_pr);
  lv_btn_set_style(btnRTwo, LV_BTN_STATE_PR, &my_red_style_rel);
  lv_obj_set_pos(btnRTwo, calcButtonX(1), rowTwo);

  labelRTwo = lv_label_create(btnRTwo, NULL);
  lv_label_set_text(labelRTwo, "Red Square");

  btnBOne = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(btnBOne, width, height);
  lv_obj_set_free_num(btnBOne, 3);
  lv_btn_set_action(btnBOne, LV_BTN_ACTION_PR, btn_press_action);
  lv_btn_set_style(btnBOne, LV_BTN_STATE_REL, &my_blue_style_pr);
  lv_btn_set_style(btnBOne, LV_BTN_STATE_PR, &my_blue_style_rel);
  lv_obj_set_pos(btnBOne, calcButtonX(2), rowTwo);

  labelBOne = lv_label_create(btnBOne, NULL);
  lv_label_set_text(labelBOne, "Blue Square");

  btnBTwo = lv_btn_create(lv_scr_act(), NULL);
  lv_obj_set_size(btnBTwo, width, height);
  lv_obj_set_free_num(btnBTwo, 4);
  lv_btn_set_action(btnBTwo, LV_BTN_ACTION_PR, btn_press_action);
  lv_btn_set_style(btnBTwo, LV_BTN_STATE_REL, &my_blue_style_pr);
  lv_btn_set_style(btnBTwo, LV_BTN_STATE_PR, &my_blue_style_rel);
  lv_obj_set_pos(btnBTwo, calcButtonX(2), rowOne);

  labelBTwo = lv_label_create(btnBTwo, NULL);
  lv_label_set_text(labelBTwo, stringBTwo.c_str());

	btnAS = lv_btn_create(lv_scr_act(),NULL);
	lv_obj_set_size(btnAS, width, height);
  lv_obj_set_free_num(btnAS, 5);
	lv_btn_set_action(btnAS, LV_BTN_ACTION_PR, btn_press_action);
	lv_btn_set_style(btnAS, LV_BTN_STATE_REL, &my_autonsk_style_pr);
	lv_btn_set_style(btnAS, LV_BTN_STATE_PR, &my_autonsk_style_rel);
	lv_obj_set_pos(btnAS, calcButtonX(3), rowOne);

	labelAS = lv_label_create(btnAS,NULL);
	lv_label_set_text(labelAS, "Auton Skills");

  btnPageFlipOne = lv_btn_create(lv_scr_act(),NULL);
  lv_obj_set_size(btnPageFlipOne, width, height);
  lv_obj_set_free_num(btnPageFlipOne, 6);
  lv_btn_set_action(btnPageFlipOne, LV_BTN_ACTION_PR, btn_press_action_alt);
  lv_btn_set_style(btnPageFlipOne, LV_BTN_STATE_REL, &my_pageflip_style_pr);
  lv_btn_set_style(btnPageFlipOne, LV_BTN_STATE_PR, &my_pageflip_style_rel);
  lv_obj_set_pos(btnPageFlipOne, calcButtonX(3), rowTwo);

  labelPageFlipOne = lv_label_create(btnPageFlipOne,NULL);
  lv_label_set_text(labelPageFlipOne, "Next Page");

}

void create_buttons_pgTwo(){

  lv_style_copy(&my_pageflip_style_pr, &lv_style_pretty_color);
  my_pageflip_style_pr.body.main_color = lv_color_hex(0x502966);
  my_pageflip_style_pr.body.grad_color = lv_color_hex(0x310b47);

  lv_style_copy(&my_pageflip_style_rel, &lv_style_pretty_color);
  my_pageflip_style_rel.body.main_color = lv_color_hex(0x502966);
  my_pageflip_style_rel.body.grad_color = lv_color_hex(0x9b30d9);

  btnPageFlipTwo = lv_btn_create(lv_scr_act(),NULL);
  lv_obj_set_size(btnPageFlipTwo, width, height);
  lv_obj_set_free_num(btnPageFlipTwo, 7);
  lv_btn_set_action(btnPageFlipTwo, LV_BTN_ACTION_PR, btn_press_action_alt);
  lv_btn_set_style(btnPageFlipTwo, LV_BTN_STATE_REL, &my_pageflip_style_pr);
  lv_btn_set_style(btnPageFlipTwo, LV_BTN_STATE_PR, &my_pageflip_style_rel);
  lv_obj_set_pos(btnPageFlipTwo, calcButtonX(1), rowOne);

  labelPageFlipTwo = lv_label_create(btnPageFlipTwo,NULL);
  lv_label_set_text(labelPageFlipTwo, "Previous Page");



}


//Display the name of the selected autonomous program
void selectionResult(){//Wait for a button to be pressed on the screen
while(!autonSelected){
  pros::delay(20);
  lv_task_handler();
}
//A delay so you can admire the color change on the buttons when they are pressed.
pros::delay(1000);

//Create a new page and a label to write errors, and selected autons.
pageADec = lv_page_create(lv_scr_act(),NULL);
lv_obj_set_size(pageADec,480,272);
labelDec = lv_label_create(pageADec, NULL);

//This switch function prints the name of the selected autonomous, and sets the start point of the robot
switch(programRun){

  case 1:
    lv_label_set_text(labelDec, "Red Rectangle");
    //setStartPoint();(make instances of position struct for all the autons)
  break;

  case 2:
    lv_label_set_text(labelDec, "Red Square");
  break;

  case 3:
    lv_label_set_text(labelDec, "Blue Square");
  break;

  case 4:
    lv_label_set_text(labelDec, "Blue Rectangle");
  break;

  case 5:
    lv_label_set_text(labelDec, "Auton Skills");
  break;

  case 0:
    lv_label_set_text(labelDec, "error");
  break;
}
}

//Run the autonomous selected via the auton selector.

void runChosenAuton(){
  lv_obj_t* pageAErr;
  pageAErr = lv_page_create(lv_scr_act(),NULL);
  lv_obj_set_size(pageAErr,480,272);
  lv_obj_t* labelErr;


  // a switch function that checks the value of programRun
  //(a variable w/ value changed in auton selector) and runs the selected auton
  switch(programRun){
    case 1:

    break;

    case 2:

    break;

    case 3:

    break;

    case 4:

    break;

    case 5:

    break;

    case 0:
      labelErr = lv_label_create(pageAErr,NULL);
      lv_label_set_text(labelErr,"You didn't choose a program.");
    break;
  }
}
