#include "SpriteEditorGUI.h"
#include "MeltEngineEditor.h"

namespace MELT_EDITOR
{
    SpriteEditorGUI::SpriteEditorGUI()
    {
        IsOpened = true;
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

        ImVec2 imageSize(_textureWidth, _textureHeight); // Set this to your texture's dimensions

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

            YAML::Node _spriteNode;

            _spriteNode["Name"] = "Some name";

            _spriteNode["Texcoord"].push_back(0.1f);
            _spriteNode["Texcoord"].push_back(0.2f);

            _spriteNode["Size"].push_back(0.5f);
            _spriteNode["Size"].push_back(1.0f);

            _root["Sprites"].push_back(_spriteNode);

            std::ofstream _file;

            std::string _path = _textureData.TextureFileLocation + "/" + _textureData.TextureFileName + ".yaml";
            _file.open(_path);
            _file << _root;
            _file.close();
        }

        ImGui::SameLine();

        if(ImGui::Button("Generate"))
        {
            CachedSpriteData.clear();

            for(std::size_t _i = 0; _i < GridSize.x; ++_i)
            {
                for(std::size_t _j = 0; _j < GridSize.y; ++_j)
                {
                    SpriteData _data;
                    _data.Position = ImVec2(static_cast<float>(_i) * _spriteSize.x, static_cast<float>(_j) * _spriteSize.y);
                    _data.Size     = _spriteSize;

                    CachedSpriteData.push_back(_data);
                }
            }
        }

        ImGui::Text("Grid size");
        ImGui::SameLine();
        ImGui::InputFloat2("##a", (float*)&GridSize);

        ImGui::Text("Cell size");
        ImGui::SameLine();
        ImGui::InputFloat2("##b", (float*)&CellSize);

        ImGui::EndChild();




        ImVec2 windowSize = ImGui::GetWindowSize();

        float xPos = (windowSize.x - _textureWidth) * 0.5f;
        float yPos = (windowSize.y - _textureHeight) * 0.5f;

        ImGui::SetCursorPos(ImVec2(xPos, yPos));
        ImGui::Image(
                (void*)(intptr_t)EditorOwner->Engine->m_RenderSystem->EditorGUIFrameBuffer->TextureID,
                imageSize);

        ImGui::SetCursorPos(ImVec2(xPos, yPos));
        ImTextureID textureID = (ImTextureID)(intptr_t)_textureData.TextureID;
        ImGui::Image(
                (void*)(intptr_t)_textureData.TextureID,
                imageSize);


        ImGui::SetCursorPos(ImVec2(xPos, yPos));

        std::size_t _column = 8;
        std::size_t _row    = 6;

        ImVec2 framePos = ImGui::GetCursorScreenPos();

//         _spriteSize = ImVec2(
//                _textureWidth / static_cast<float>(_column),
//                _textureHeight / static_cast<float>(_row));

        ImU32 frameColor = ImGui::GetColorU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red color
        float frameThickness = 1.0f;

        ImDrawList* _drawList = ImGui::GetWindowDrawList();

        for(const SpriteData& _data : CachedSpriteData)
        {
            ImVec2 _offset = _data.Position;

            ImVec2 _upperLeft  (framePos.x                 + _offset.x, framePos.y                + _offset.y);
            ImVec2 _lowerRight (framePos.x + _data.Size.x  + _offset.x, framePos.y + _data.Size.y + _offset.y);

            _drawList->AddRect(
                    _upperLeft,
                    _lowerRight,
                    frameColor,
                    0.0f, 0, frameThickness);
        }

//        for(std::size_t _i = 0; _i < _column; ++_i)
//        {
//            for(std::size_t _j = 0; _j < _row; ++_j)
//            {
//                ImVec2 _offset(static_cast<float>(_i) * _spriteSize.x, static_cast<float>(_j) * _spriteSize.y);
//
//                ImVec2 _upperLeft  (framePos.x               + _offset.x, framePos.y                   + _offset.y);
//                ImVec2 _lowerRight (framePos.x + _spriteSize.x + _offset.x, framePos.y + _spriteSize.y + _offset.y);
//
//                _drawList->AddRect(
//                        _upperLeft,
//                        _lowerRight,
//                        frameColor,
//                        0.0f, 0, frameThickness);
//            }
//        }











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
        ImGui::PopStyleColor(1);
    }
}