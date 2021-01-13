static void newcam_angle_rotate(struct newcam_hardpos *params)
{
    newcam_yaw += 0x100;
    print_text(32,32,"hi i am a script");
    print_text_fmt_int(32,48,"%d",newcam_yaw);
}


static void newcam_parallel_cam(struct newcam_hardpos *params);

static void newcam_c_up_cam(struct newcam_hardpos *params) {
	newcam_distance_target = 175;

	newcam_yaw += (s32)gPlayer1Controller->stickX * 6;
	newcam_tilt += (s32)gPlayer1Controller->stickY * 6;

	if (gPlayer1Controller->buttonPressed & D_CBUTTONS) {
		params->newcam_hard_script = newcam_parallel_cam;
		newcam_tilt = 1500;
		newcam_yaw = -gMarioState->faceAngle[1]-0x4000;
		set_mario_action(gMarioState, ACT_IDLE, 0);
	}
}

static void newcam_parallel_cam(struct newcam_hardpos *params) {
	newcam_distance_target = 1000;

    params->newcam_hard_lookX = (s16)(gMarioState->pos[0]);
	params->newcam_hard_lookY = (s16)(gMarioState->pos[1] + 125.0f);
    params->newcam_hard_lookZ = (s16)(gMarioState->pos[2]);

	if (gPlayer1Controller->buttonPressed & R_CBUTTONS)
		newcam_yaw -= 0x2000;
	if (gPlayer1Controller->buttonPressed & L_CBUTTONS)
		newcam_yaw += 0x2000;
	if (gPlayer1Controller->buttonPressed & U_CBUTTONS) {
		if (gMarioState->action & ACT_FLAG_ALLOW_FIRST_PERSON) {
			newcam_yaw = -gMarioState->faceAngle[1]-0x4000;
			params->newcam_hard_script = newcam_c_up_cam;
			set_mario_action(gMarioState, ACT_WAITING_FOR_DIALOG, 0);
		}
	}

	if (gPlayer1Controller->buttonPressed & U_JPAD) {
		newcam_yaw = -gMarioState->faceAngle[1]-0x4000;
	}
	if (gPlayer1Controller->buttonPressed & D_JPAD) {
		newcam_yaw = newcam_yaw % 0x2000 >= 0x1000 ?
					 newcam_yaw + 0x2000 - (newcam_yaw % 0x2000) :
					 newcam_yaw - (newcam_yaw % 0x2000);
	}
	if (gPlayer1Controller->buttonDown & R_JPAD)
		newcam_yaw += 100;
	if (gPlayer1Controller->buttonDown & L_JPAD)
		newcam_yaw -= 100;
}