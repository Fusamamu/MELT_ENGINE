#ifndef BONE_H
#define BONE_H

#include "Core.h"
#include "Util.h"

namespace MELT::ANIMATION
{
    struct KeyPosition
    {
        M_VEC3 position;
        float  time_stamp;
    };

    struct KeyRotation
    {
        glm::quat orientation;
        float time_stamp;
    };

    struct KeyScale
    {
        M_VEC3 scale;
        float time_stamp;
    };

    class Bone
    {
    public:
        Bone(const std::string& _name, int _id, const aiNodeAnim* _channel):
            m_name(_name),
            m_id  (_id),
            m_local_transform(1.0f)
        {
            m_num_positions = _channel->mNumPositionKeys;

            for(int _position_idx = 0; _position_idx < m_num_positions; ++_position_idx)
            {
                aiVector3D _ai_position = _channel->mPositionKeys[_position_idx].mValue;
                float _time_stamp       = _channel->mPositionKeys[_position_idx].mTime; 
                
                KeyPosition _data;
                _data.position   = UTIL::AssimpGLMHelpers::GetGLMVec(_ai_position);
                _data.time_stamp = _time_stamp;

                m_positions.push_back(_data);
            }

            m_num_rotations = _channel->mNumRotationKeys;
            
            for(int _rotation_idx = 0; _rotation_idx < m_num_rotations; ++_rotation_idx)
            {
                aiQuaternion _ai_orientation = _channel->mRotationKeys[_rotation_idx].mValue;
                float _time_stamp            = _channel->mRotationKeys[_rotation_idx].mTime;
                
                KeyRotation _data;
                
            }
        }
    private:

        int m_id;
        std::string m_name;

        std::vector<KeyPosition> m_positions;
        std::vector<KeyRotation> m_rotations;
        std::vector<KeyScale>    m_scales;
        
        int m_num_positions;
        int m_num_rotations;
        int m_num_scalings;
        
        glm::mat4 m_local_transform;
    };
}

#endif
