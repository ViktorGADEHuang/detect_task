/*
 *                        .::::.
 *                      .::::::::.
 *                     :::::::::::
 *                  ..:::::::::::'
 *               '::::::::::::'
 *                 .::::::::::
 *            '::::::::::::::..
 *                 ..::::::::::::.
 *               ``::::::::::::::::
 *                ::::``:::::::::'        .:::.
 *               ::::'   ':::::'       .::::::::.
 *             .::::'      ::::     .:::::::'::::.
 *            .:::'       :::::  .:::::::::' ':::::.
 *           .::'        :::::.:::::::::'      ':::::.
 *          .::'         ::::::::::::::'         ``::::.
 *      ...:::           ::::::::::::'              ``::.
 *     ````':.          ':::::::::'                  ::::..
 *                        '.:::::'                    ':'````..
 */

/*
ʹ�ã�ʹ����ֻ����ͷ�ļ����豸�б�����Ӷ�Ӧ���豸���ں���detect_init����Ӷ�Ӧ�����ݣ�����Ҫʹ�õ��豸��ʹ�ú���communication_frame_rate_update
����ͨ��֡�ʼ���

ע�⣺�˴��벻����while1��ѭ��������detect_init�е�max_offline_frame_rateΪ���ʧ��֡�ʣ���Ҫ�Լ�����
*/





#include "detect_task.h"

#include "stdio.h"

/**
  * @brief          init
  * @param[in]      none
  * @retval         none
  */
static void detect_init(void);


toe_offline_t toe_offline[ERROR_LIST_LENGHT] = {0};


#if INCLUDE_uxTaskGetStackHighWaterMark       
	uint32_t detect_task_stack;
#endif



/**
  * @brief          init
  * @param[in]      none
  * @retval         none
  */
static void detect_init(void)
{
  uint8_t i = 0;
  uint16_t max_offline_frame_rate[ERROR_LIST_LENGHT] =
      {
          DBUS_MAX_OFFLINE_FRAME_RATE,
          CHASSIS_MOTOR_1_MAX_OFFLINE_FRAME_RATE,
          CHASSIS_MOTOR_2_MAX_OFFLINE_FRAME_RATE, // chassis_motor2
          CHASSIS_MOTOR_3_MAX_OFFLINE_FRAME_RATE, // chassis_motor3
          CHASSIS_MOTOR_4_MAX_OFFLINE_FRAME_RATE, // chassis_motor4
          FRIC_R_MAX_OFFLINE_FRAME_RATE,          // fric_r
          FRIC_L_MAX_OFFLINE_FRAME_RATE,          // fric_l
          TRIG_MAX_OFFLINE_FRAME_RATE,            // trig
          YAW_MAX_OFFLINE_FRAME_RATE,             // yaw
          PITCH_MAX_OFFLINE_FRAME_RATE,           // pitch
      };
        
  for (i = 0; i < ERROR_LIST_LENGHT; i++)
  {
    toe_offline[i].offline_frame_rate = 0;
    toe_offline[i].max_offline_frame_rate = max_offline_frame_rate[i];
    toe_offline[i].communication_state = COMMUNICATION_MORMAL;
    toe_offline[i].toe_offline_data_handle_f = NULL;
    toe_offline[i].toe_unable_f = NULL;
    toe_offline[i].toe_connect_soft_restart_f = NULL;
  }

  // toe_offline[DBUS_TOE].toe_offline_data_handle_f = RC_data_is_error;
  // toe_offline[DBUS_TOE].toe_unable_f = slove_RC_lost;
  // toe_offline[DBUS_TOE].toe_connect_soft_restart_f = slove_data_error;
}




/**
  * @brief          detect task
  * @param[in]      pvParameters: NULL
  * @retval         none
  */
void detect_task(void const *argument)
{
  uint8_t i = 0;
  for (i = 0; i < ERROR_LIST_LENGHT; i++)
  {
    toe_offline[i].offline_frame_rate++;
    if (toe_offline[i].offline_frame_rate > toe_offline[i].max_offline_frame_rate)
    {
      toe_offline[i].communication_state = COMMUNICATION_NONE;
      toe_offline[i].offline_frame_rate = toe_offline[i].max_offline_frame_rate;
      if (toe_offline[i].toe_offline_data_handle_f != NULL)
      {
        toe_offline[i].toe_offline_data_handle_f();
      }
    }
    else
    {
      toe_offline[i].communication_state = COMMUNICATION_MORMAL;
    }
  }
  vTaskDelay(DETECT_CONTROL_TIME);
  #if INCLUDE_uxTaskGetStackHighWaterMark
    detect_task_stack = uxTaskGetStackHighWaterMark(NULL);
  #endif
}


/**
  * @brief          get toe error status
  * @param[in]      toe: table of equipment
  * @retval         true (eror) or false (no error)
  */
bool toe_is_error(uint8_t toe)
{
  if (COMMUNICATION_NONE == toe_offline[toe].communication_state)
  {
    return true;
  }
  else
  {
    return false;
  }
}


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
void communication_frame_rate_update(uint8_t toe)
{
  toe_offline[toe].offline_frame_rate = 0;
}


