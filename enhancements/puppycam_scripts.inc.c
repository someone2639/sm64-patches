static void newcam_angle_rotate(struct newcam_hardpos *params)
{
    newcam_yaw += 0x100;
    print_text(32,32,"hi i am a script");
    print_text_fmt_int(32,48,"%d",newcam_yaw);
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
	if (gPlayer1Controller->buttonPressed & U_CBUTTONS)
		newcam_tilt += 0x1000;
	if (gPlayer1Controller->buttonPressed & D_CBUTTONS)
		newcam_tilt -= 0x1000;

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