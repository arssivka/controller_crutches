/**
 *  @autor arssivka
 *  @date 9/20/17
 */

#pragma once


#include <utility>
#include <motion/MotionModule.h>
#include <math/AngleTools.h>
#include <motion/Kinematics.h>
#include <MX28.h>

namespace Robot {
    class Kicking
            : public MotionModule {
    public:
        enum {
            PHASE_DONE = 0, // Kick are done
            PHASE_SHIFTING_BODY = 1, // Shift center mass
            PHASE_KICKING = 2, // Kicking
            PHASE_RESTORING = 3  // Go back
        };

        enum {
            RIGHT_LEG = 0,
            LEFT_FEG = 1
        };

    public:
        static Kicking* GetInstance();

        void Kick();

        bool IsRunning() const noexcept;

        void Initialize() override;

        void Process() override;

        void Break();

        int GetKickingLeg() const noexcept;

        void SetKickingLeg(int kicking_leg) noexcept;

        float GetKickTargetXOffset() const noexcept;

        void SetKickTargetXOffset(float kick_target_x_offset) noexcept;

        float GetKickTargetYOffset() const noexcept;

        void SetKickTargetYOffset(float kick_target_y_offset) noexcept;

        float GetKickXOffset() const noexcept;

        void SetKickXOffset(float kick_x_offset) noexcept;

        float GetKickYOffset() const noexcept;

        void SetKickYOffset(float kick_y_offset) noexcept;

        float GetLickZOffset() const noexcept;

        void SetKickZOffset(float kick_z_offset) noexcept;

        float GetKickYawOffset() const noexcept;

        void SetKickYawOffset(float kick_yaw_offset) noexcept;

        float GetShiftingBodyDuration() const noexcept;

        void SetShiftingBodyDuration(float shifting_body_duration) noexcept;

        float GetKickingDuration() const noexcept;

        void SetKickingDuration(float kicking_duration) noexcept;

        float GetRestoringDuration() const noexcept;

        void SetRestoringDuration(float restoring_duration) noexcept;

        float GetBodyInitXOffset() const noexcept;

        void SetBodyInitXOffset(float body_init_x_offset) noexcept;

        float GetBodyInitYOffset() const noexcept;

        void SetBodyInitYOffset(float body_init_y_offset) noexcept;

        float GetBodyInitZOffset() const noexcept;

        void SetBodyInitZOffset(float body_init_z_offset) noexcept;

        float GetBodyInitPitchOffset() const noexcept;

        void SetBodyInitPitchOffset(float body_init_pitch_offset) noexcept;

        float GetBodyXOffset() const noexcept;

        void SetBodyXOffset(float body_x_offset) noexcept;

        float GetBodyYOffset() const noexcept;

        void SetBodyYOffset(float body_y_offset) noexcept;

        float GetBodyZOffset() const noexcept;

        void SetBodyZOffset(float body_z_offset) noexcept;

        float GetArmSwingGain() const noexcept;

        void SetArmSwingGain(float arm_swing_gain) noexcept;

        float GetBalanceRollGain() const noexcept;

        void SetBalanceRollGain(float balance_roll_gain) noexcept;

        float GetBalancePitchGain() const noexcept;

        void SetBalancePitchGain(float balance_pitch_gain) noexcept;

        bool GetBalanceEnabled() const noexcept;

        void SetBalanceEnabled(bool balance_enabled) noexcept;

    private:
        Kicking() = default;

        void UpdateTimeParameters();

        void UpdateActiveParams() noexcept;

    private:
        bool m_debug{true};

        int m_kicking_leg{RIGHT_LEG};
        float m_kick_target_x_offset{0.0f};
        float m_kick_target_y_offset{0.0f};
        float m_kick_x_offset{0.0f};
        float m_kick_y_offset{0.0f};
        float m_kick_z_offset{0.0f};
        float m_kick_yaw_offset{0.0f};

        int m_cur_kicking_leg{RIGHT_LEG};
        float m_cur_kick_target_x_offset{0.0f};
        float m_cur_kick_target_y_offset{0.0f};
        float m_cur_kick_x_offset{0.0f};
        float m_cur_kick_y_offset{0.0f};
        float m_cur_kick_z_offset{0.0f};
        float m_cur_kick_yaw_offset{0.0f};

        float m_shifting_body_duration{100.0f};
        float m_kicking_duration{30.0f};
        float m_restoring_duration{80.0f};

        float m_cur_shifting_body_duration{0.0f};
        float m_cur_kicking_duration{0.0f};
        float m_cur_restoring_duration{0.0f};

        float m_body_init_x_offset{-10.0f};
        float m_body_init_y_offset{0.0f};
        float m_body_init_z_offset{-5.0f};
        float m_body_init_pitch_offset{radians(-15.0f)};

        float m_cur_body_init_x_offset{0.0f};
        float m_cur_body_init_y_offset{-15.0f};
        float m_cur_body_init_z_offset{0.0f};
        float m_cur_body_init_pitch_offset{0.0f};

        float m_body_x_offset{-20.0f};
        float m_body_y_offset{-15.0f};
        float m_body_z_offset{-5.0f};

        float m_cur_body_x_offset{0.0f};
        float m_cur_body_y_offset{0.0f};
        float m_cur_body_z_offset{0.0f};
        float m_cur_body_pitch_offset{0.0f};

        float m_arm_swing_gain{0.0f};
        float m_balance_roll_gain{0.0f};
        float m_balance_pitch_gain{0.0f};
        bool m_balance_enabled{true};

        float m_cur_arm_swing_gain{0.0f};
        float m_cur_balance_roll_gain{0.0f};
        float m_cur_balance_pitch_gain{0.0f};
        bool m_cur_balance_enabled{true};

        float m_time{0.0f};
        int m_phase{PHASE_DONE};
        bool m_kicking_done{true};
    };
}


