#include "SpriteEditorGUI.h"
#include "MeltEngineEditor.h"

namespace MELT_EDITOR
{
    SpriteEditorGUI::SpriteEditorGUI()
    {
        IsOpened = true;
    }

    void SpriteEditorGUI::Init()
    {
        auto& _textureData = EditorOwner->Engine->TextureMng.TextureDataTable["blacknwhite"];

        //std::string _path = _textureData.TextureFileLocation + _textureData.TextureFileName + ".yaml";

        //Temp
        //_textureData.SpriteSheetPath = _path;

        //std::cout << _path << std::endl;

        YAML::Node node = YAML::LoadFile(_textureData.SpriteSheetPath);

        //std::cout << node["Sprite sheet name"] << std::endl;

        GridSize.x = node["Grid size"][0].as<float>();
        GridSize.y = node["Grid size"][1].as<float>();

        GenerateSpriteByGridSetting();
    }

    void SpriteEditorGUI::GenerateSpriteByGridSetting()
    {
        auto& _textureData = EditorOwner->Engine->TextureMng.TextureDataTable["blacknwhite"];

        float _textureWidth  = static_cast<float>(_textureData.Width ) * 4.0f;
        float _textureHeight = static_cast<float>(_textureData.Height) * 4.0f;

        ImVec2 _textureSize(_textureWidth, _textureHeight); // Set this to your texture's dimensions

        glm::vec2 _spriteSize = glm::vec2
                (
                        _textureWidth  / static_cast<float>(GridSize.x),
                        _textureHeight / static_cast<float>(GridSize.y)
                );

        CachedSpriteData.clear();

        for(std::size_t _i = 0; _i < GridSize.x; ++_i)
        {
            for(std::size_t _j = 0; _j < GridSize.y; ++_j)
            {
                auto _if = static_cast<float>(_i);
                auto _jf = static_cast<float>(_j);

                MELT::SpriteData _data;
                _data.Name     = std::to_string(_i) + std::to_string(_j);
//                _data.Position = ImVec2(_if * _spriteSize.x, _jf * _spriteSize.y);
//                _data.Size     = _spriteSize;

                _data.Position = glm::vec2(_if * _spriteSize.x, _jf * _spriteSize.y);
                _data.Size     = _spriteSize;

                glm::vec2 _coordOffset (_if * 1.0f/GridSize.x, _jf * 1.0f/GridSize.y);

                _data.TexCoords[0] = glm::vec2(1.0f/GridSize.x + _coordOffset.x, 0.0f            + _coordOffset.y);
                _data.TexCoords[1] = glm::vec2(1.0f/GridSize.x + _coordOffset.x, 1.0f/GridSize.y + _coordOffset.y);
                _data.TexCoords[2] = glm::vec2(0.0f            + _coordOffset.x, 1.0f/GridSize.y + _coordOffset.y);
                _data.TexCoords[3] = glm::vec2(0.0f            + _coordOffset.x, 0.0f            + _coordOffset.y);

                CachedSpriteData.push_back(_data);
            }
        }
    }

    void SpriteEditorGUI::Open()
    {
        IsOpened = true;
    }

    void SpriteEditorGUI::Close()
    {
        IsOpened = false;
    }

    static ImVec2 childPos  = ImVec2(50, 50);  // Starting position within the parent window
    static ImVec2 childSize = ImVec2(200, 150);

    void SpriteEditorGUI::DrawGUI()
    {
        if(!IsOpened)
            return;

        auto& _textureData = EditorOwner->Engine->TextureMng.TextureDataTable["blacknwhite"];

        float _textureWidth  = static_cast<float>(_textureData.Width ) * 4.0f;
        float _textureHeight = static_cast<float>(_textureData.Height) * 4.0f;

        ImVec2 _textureSize(_textureWidth, _textureHeight); // Set this to your texture's dimensions

        ImVec2 _spriteSize = ImVec2
                (
                    _textureWidth  / static_cast<float>(GridSize.x),
                    _textureHeight / static_cast<float>(GridSize.y)
                );

        ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(33, 36, 35, 255));
        ImGui::Begin("Sprite Editor", &IsOpened);

        ImGui::BeginChild("##Edit");

        if(ImGui::Button("SAVE"))
        {
            YAML::Node _root;

            _root["Sprite sheet name"] = _textureData.TextureFileName;

            _root["Grid size"].push_back(GridSize.x);
            _root["Grid size"].push_back(GridSize.y);

            _root["Cell size"].push_back(CellSize.x);
            _root["Cell size"].push_back(CellSize.y);

            for(const MELT::SpriteData& _data : CachedSpriteData)
            {
                YAML::Node _spriteNode;

                _spriteNode["Name"] = _data.Name;

                _spriteNode["Pos"].push_back(_data.Position.x);
                _spriteNode["Pos"].push_back(_data.Position.y);

                _spriteNode["Size"].push_back(_data.Size.x);
                _spriteNode["Size"].push_back(_data.Size.y);

                for (size_t i = 0; i < _data.TexCoords.size(); ++i)
                {
                    YAML::Node _vecNode;
                    _vecNode["x"] = _data.TexCoords[i].x;
                    _vecNode["y"] = _data.TexCoords[i].y;
                    _spriteNode["TexCoords"].push_back(_vecNode);
                }

                _root["Sprites"].push_back(_spriteNode);
            }

            std::ofstream _file;
            std::filesystem::path _path = _textureData.TextureFileLocation + "/" + _textureData.TextureFileName + ".yaml";
            _file.open(_path);
            _file << _root;
            _file.close();

            _textureData.SpriteSheetPath = _path;
        }

        ImGui::SameLine();

        if(ImGui::Button("Generate"))
            GenerateSpriteByGridSetting();

        ImGui::Text("Grid size");
        ImGui::SameLine();
        ImGui::InputFloat2("##a", (float*)&GridSize);
        ImGui::Text("Cell size");
        ImGui::SameLine();
        ImGui::InputFloat2("##b", (float*)&CellSize);
        ImGui::EndChild();

        ImVec2 windowSize = ImGui::GetWindowSize();

        float _cursorPosX = (windowSize.x - _textureWidth ) * 0.5f;
        float _cursorPosY = (windowSize.y - _textureHeight) * 0.5f;

        ImGui::SetCursorPos(ImVec2(_cursorPosX, _cursorPosY));
        ImGui::Image((void*)(intptr_t)EditorOwner->Engine->m_RenderSystem->EditorGUIFrameBuffer->TextureID,_textureSize);
        ImGui::SetCursorPos(ImVec2(_cursorPosX, _cursorPosY));
        ImGui::Image((void*)(intptr_t)_textureData.TextureID, _textureSize);

        ImGui::SetCursorPos(ImVec2(_cursorPosX, _cursorPosY));

        ImDrawList* _drawList = ImGui::GetWindowDrawList();

        ImVec2 _framePos  = ImGui::GetCursorScreenPos();
        ImU32 _frameColor = ImGui::GetColorU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
        float _frameThickness = 1.0f;

        for(const MELT::SpriteData& _data : CachedSpriteData)
        {
            ImVec2 _offset = ImVec2(_data.Position.x, _data.Position.y);

            ImVec2 _upperLeft  (_framePos.x + _offset.x               , _framePos.y + _offset.y               );
            ImVec2 _lowerRight (_framePos.x + _data.Size.x + _offset.x, _framePos.y + _data.Size.y + _offset.y);

            _drawList->AddRect(
                    _upperLeft,
                    _lowerRight,
                    _frameColor,
                    0.0f, 0, _frameThickness);
        }

//        ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(100, 100, 100, 255));
//        ImGui::SetCursorPos(childPos);
//        ImGui::BeginChild("Draggable Child", childSize, true, ImGuiWindowFlags_NoScrollbar);
//
//        ImGui::Text("This is a draggable child window.");
//        ImGui::Text("You can add more content here.");
//
//        if (ImGui::IsWindowHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
//        {
//            ImVec2 dragDelta = ImGui::GetMouseDragDelta();
//            childPos.x += dragDelta.x;
//            childPos.y += dragDelta.y;
//            ImGui::ResetMouseDragDelta();
//        }
//        ImGui::EndChild();
//        ImGui::PopStyleColor();

        ImGui::End();
        ImGui::PopStyleColor();
    }
}