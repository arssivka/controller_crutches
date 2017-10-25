/**
 * Copyright 2016 Arseniy Ivin <arssivka@yandex.ru>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @autor arssivka
 *  @date 5/3/17
 */

#include "GoTo.h"
#include "motion/modules/Walking.h"

#define PI (3.14159265)


bool Robot::GoTo::IsDone() const {
    return m_Done;
}

void Robot::GoTo::Process(Robot::Pose2D pos) {
    m_Done = true;
    float dist = hypot(pos.X(), pos.Y());
    float angle = atan2(pos.Y(), pos.X()) / M_PI * 180.0;

    if (!Walking::GetInstance()->IsRunning() ||
        Walking::GetInstance()->GetXMoveAmplitude() != m_X ||
        Walking::GetInstance()->GetXMoveAmplitude() != m_Y ||
        Walking::GetInstance()->GetXMoveAmplitude() != m_A) {
        m_X = Walking::GetInstance()->GetXMoveAmplitude();
        m_Y = Walking::GetInstance()->GetYMoveAmplitude();
        m_A = Walking::GetInstance()->GetAMoveAmplitude();
    }


    if (dist > m_DistanceVar) {
        m_A = 0;
        m_GoalMaxSpeed = (dist < m_FitDistance) ? m_FitSpeed : m_MaxSpeed;

        float x_factor = pos.X() / dist;
        float x_speed = x_factor * m_GoalMaxSpeed;
        float y_factor = pos.Y() / dist;
        float y_speed = y_factor * m_GoalMaxSpeed;

        m_X += m_StepAccel * x_factor;
        if (x_speed > 0 && m_X > x_speed || x_speed <= 0 && m_X < x_speed) {
            m_X = x_speed;
        }

        m_Y += m_StepAccel * y_factor;
        if (y_speed > 0 && m_Y > y_speed || y_speed <= 0 && m_Y < y_speed) {
            m_Y = y_speed;
        }

        m_Done = false;
    } else {
        m_X = 0;
        m_Y = 0;
    }

    if (m_Done) {
        float deg = pos.Theta() / PI * 180;
        if (deg > 0 && deg > m_AngleVar || deg < 0 && deg < -m_AngleVar) {
            m_GoalTurn = m_MaxTurn;
            if (deg < 0) {
                m_A -= m_TurnAccel;
                if (m_A < -m_GoalTurn) m_A = -m_GoalTurn;
            } else {
                m_A += m_TurnAccel;
                if (m_A > m_GoalTurn) m_A = m_GoalTurn;
            }
            m_Done = false;
        } else {
            m_A = 0;
        }
    }


    if (!m_Done) {
        Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
        Walking::GetInstance()->SetXMoveAmplitude(m_X);
        Walking::GetInstance()->SetYMoveAmplitude(m_Y);
        Walking::GetInstance()->SetAMoveAmplitude(m_A);
        Walking::GetInstance()->Start();
    } else {
        Walking::GetInstance()->Stop();
    }
}

Robot::GoTo::GoTo() {
    m_MaxSpeed = 20.0;
    m_FitSpeed = 3.0;
    m_MaxTurn = 35.0;
    m_StepAccel = 1.0;
    m_TurnAccel = 1.0;

    m_FitDistance = 200.0;
    m_DistanceVar = 50.0;
    m_AngleVar = 10.0;

    m_GoalMaxSpeed = 0.0;
    m_GoalTurn = 0.0;

    m_X = 0.0;
    m_Y = 0.0;
    m_A = 0.0;

    m_Done = false;
}
