/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * AVR Software Framework (ASF).
 */
#include <asf.h>
#include "sysclk.h"
#include "sleepmgr.h"
#include "led.h"
#include "delay.h"
//#include "stdio_serial.h"
#include "print_util.h"
#include "generator.h"

#include "time_keeper.h"
#include "i2c_driver_int.h"
#include "qfilter.h"
#include "stabilisation.h"
#include "streams.h"

#include "bmp085.h"

#include "scheduler.h"
#include "boardsupport.h"
#include "mavlink_actions.h"

board_hardware_t *board;

pressure_data *pressure;


NEW_TASK_SET(main_tasks, 10)

task_return_t run_stabilisation() {
	board->controls.rpy[ROLL]=-getChannel(S_ROLL)/350.0;
	board->controls.rpy[PITCH]=-getChannel(S_PITCH)/350.0;
	board->controls.rpy[YAW]=getChannel(S_YAW)/350.0;
	board->controls.thrust=getChannel(S_THROTTLE)/350.0;

	imu_update(&(board->imu1));
	if (getChannel(4)>0) {
		quad_stabilise(&(board->imu1), &(board->controls), RATE_COMMAND_MODE);
	} else {
		quad_stabilise(&(board->imu1), &(board->controls), ATTITUDE_COMMAND_MODE);
	}

}

void initialisation() {
	int i;
	irq_initialize_vectors();
	cpu_irq_enable();
	Disable_global_interrupt();
	
	// Initialize the sleep manager
	sleepmgr_init();

	sysclk_init();
	board_init();
	delay_init(sysclk_get_cpu_hz());
	init_time_keeper();

	
	INTC_init_interrupts();
	
	board=initialise_board();
	
	if (init_i2c(0)!=STATUS_OK) {
		//putstring(STDOUT, "Error initialising I2C\n");
		while (1==1);
	} else {
		//putstring(STDOUT, "initialised I2C.\n");
	};

	
	Enable_global_interrupt();
		
	dbg_print("Debug stream initialised\n");

	LED_Off(LED1);
	
/*
	set_servo(0, -500, -500);
	set_servo(1, -500, -500);
	set_servo(2, -500, -500);
	set_servo(3, -500, -500);
*/
	
	set_servo(0, -600, -600);
	set_servo(1, -600, -600);
	set_servo(2, -600, -600);
	set_servo(3, -600, -600);
	
	//delay_ms(1000);
	init_stabilisation();

	init_onboard_parameters();
	init_mavlink_actions();
	
	board->imu1.attitude.calibration_level=LEVELING;	
	for (i=200; i>0; i--) {
		imu_update(&board->imu1);
		if (i%50 ==0) {
			// Send heartbeat message
			mavlink_msg_heartbeat_send(MAVLINK_COMM_0, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC, MAV_MODE_STABILIZE_ARMED, 0, MAV_STATE_CALIBRATING);
		}
		
		delay_ms(5);
	}
	board->imu1.attitude.calibration_level=OFF;
	
}

void main (void)
{
	int i=0;
	int counter=0;
	uint32_t last_looptime, this_looptime;

	initialisation();
	
	init_scheduler(&main_tasks);
	
	register_task(&main_tasks, 0, 2000, &run_stabilisation );
	register_task(&main_tasks, 1, 10000, &mavlink_protocol_update);
	// main loop
	counter=0;
	while (1==1) {
		this_looptime=get_millis();
		

		
		run_scheduler_update(&main_tasks);

		
		LED_On(LED1);
		delay_ms(1);
		counter=(counter+1)%1000;
		last_looptime=this_looptime;	
	}		
}


