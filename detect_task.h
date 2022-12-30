/*
 * @Date: 2022-11-29 18:23:50
 * @LastEditTime: 2022-12-30 11:08:18
 * @FilePath: \detect\detect_task.h
 * @Description: �������ͷ�ļ�
 * 
 */
#ifndef __DETECT_TASK_H
#define __DETECT_TASK_H

#include "struct_typedef.h"

#include "stdbool.h"

#define DETECT_TASK_INIT_TIME 57
#define DETECT_CONTROL_TIME 5

#define COMMUNICATION_MORMAL   0
#define COMMUNICATION_NONE     1

#define USE_DETECT


#define DBUS_MAX_OFFLINE_FRAME_RATE               20
#define CHASSIS_MOTOR_1_MAX_OFFLINE_FRAME_RATE    10
#define CHASSIS_MOTOR_2_MAX_OFFLINE_FRAME_RATE    10
#define CHASSIS_MOTOR_3_MAX_OFFLINE_FRAME_RATE    10
#define CHASSIS_MOTOR_4_MAX_OFFLINE_FRAME_RATE    10
#define FRIC_R_MAX_OFFLINE_FRAME_RATE             10
#define FRIC_L_MAX_OFFLINE_FRAME_RATE             10
#define TRIG_MAX_OFFLINE_FRAME_RATE               10
#define YAW_MAX_OFFLINE_FRAME_RATE                50
#define PITCH_MAX_OFFLINE_FRAME_RATE              50



//�豸�б�
enum TOEList
{
  DBUS_TOE = 0,
  CHASSIS_MOTOR1_TOE,
  CHASSIS_MOTOR2_TOE,
  CHASSIS_MOTOR3_TOE,
  CHASSIS_MOTOR4_TOE,
  FRICR_MOTOR_R_TOE,
  FRICR_MOTOR_L_TOE,
  TRIGGER_MOTOR_TOE,
  YAW_GIMBAL_MOTOR_TOE,
  PITCH_GIMBAL_MOTOR_TOE,
  //    BOARD_GYRO_TOE,
  //    BOARD_ACCEL_TOE,
  //    BOARD_MAG_TOE,
  //    REFEREE_TOE,
  //    OLED_TOE,
  ERROR_LIST_LENGHT,
};



typedef struct 
{
  /* data */
  uint32_t offline_frame_rate;                  //�豸ʧ��֡��
  uint32_t max_offline_frame_rate;              //�豸���ʧ��֡��
  uint8_t communication_state;                  //ͨ��״̬
  bool_t (*toe_offline_data_handle_f)(void);    //�豸ʧ�����ݴ���
  void (*toe_unable_f)(void);                      //�豸ʧ����ʧ��
  void (*toe_connect_soft_restart_f)(void);          //�豸ʧ��������ʹ��
}toe_offline_t;





/**
  * @brief          get toe error status
  * @param[in]      toe: table of equipment
  * @retval         true (eror) or false (no error)
  */
bool toe_is_error(uint8_t err);

/**
  * @brief          communication_frame_rate_update
  * @param[in]      toe: table of equipment
  * @retval         none
  */
/**
  * @brief          ͨ��֡�ʸ���
  * @param[in]      toe:�豸���
  * @retval         none
  */
void communication_frame_rate_update(uint8_t toe);

#endif

