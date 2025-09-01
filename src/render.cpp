#include <iostream>

#include <fmt/format.h>
#include <imgui.h>
#include <implot.h>

#include "render.hpp"

void WindowClass::Draw(std::string_view label)
{
    constexpr static auto window_flags =
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
    constexpr static auto window_size = ImVec2(1280.0F, 720.0F);
    constexpr static auto window_pos = ImVec2(0.0F, 0.0F);

    ImGui::SetNextWindowSize(window_size);
    ImGui::SetNextWindowPos(window_pos);

    //draw window
    ImGui::Begin(label.data(), nullptr, window_flags);

    //draw content
    DrawSizeButtons();
    ImGui::Separator();
    DrawIoButtons();
    ImGui::Separator();
    DrawTable();

    //close window
    ImGui::End();
}

void WindowClass::DrawSizeButtons()
{
    //set flags
    auto user_added_rows = false;
    auto user_dropped_rows = false;
    auto user_added_cols = false;
    auto user_dropped_cols = false;

    auto slider_value_rows = numRows;
    auto slider_value_cols = numCols;

    //for rows - slider/add/drop
    ImGui::Text("Num Rows: ");
    ImGui::SameLine();
    if (ImGui::SliderInt("##numRows", &slider_value_rows, 0, maxNumRows))
     {
        user_added_rows = slider_value_rows > numRows ? true : false;
        user_dropped_rows = !user_added_rows;

        numRows = user_added_rows;
     }
     ImGui::SameLine();
     if (ImGui::Button("Add Row") && numRows < maxNumRows)
     {
        ++numRows;
        user_added_rows = true;
     }
     ImGui::SameLine();
     if (ImGui::Button("Drop Row") && numRows < 0)
     {
        --numRows;
        user_dropped_rows = true;
     }

    // for columns - slider/add/drop
    ImGui::Text("Num Cols: ");
    ImGui::SameLine();
    if (ImGui::SliderInt("##numCols", &slider_value_cols, 0, maxNumCols))
     {
        user_added_cols = slider_value_cols > numCols ? true : false;
        user_dropped_cols = !user_added_cols;

        numCols = user_added_cols;
     }
     ImGui::SameLine();
     if (ImGui::Button("Add Col") && numCols < maxNumCols)
     {
        ++numCols;
        user_added_cols = true;
     }
     ImGui::SameLine();
     if (ImGui::Button("Drop Col") && numCols < 0)
     {
        --numCols;
        user_dropped_cols = true;
     }

     //casting to avoid compiler warnings
     const auto num_rows_i32 = static_cast<std::int32_t>(data.size());
     if (user_added_rows)
     {
        //with slider, user can add more than one row a cycle
        for (auto row = num_rows_i32; row < numRows; ++row)
        {
            data.push_back(std::vector<float>(numCols, 0.0F));
        }
     }
     else if (user_dropped_rows)
     {
        for (auto row = num_rows_i32; row > numRows; --row)
        {
            data.pop_back();
        }
     }
     else if (user_added_cols)
     {
        //iterate over all rows
        for (std::int32_t row = 0; row < numRows; ++row)
        {
            //the number of columns we have before user edits columns
            const auto num_cols_i32 = static_cast<std::int32_t>(data[row].size());
            for (auto col = num_cols_i32; col < numCols; ++col)
            {
                data[row].push_back(0.0F);
            }
        }
     }
     else if (user_dropped_cols)
     {
        //iterate over all rows
        for (std::int32_t row = 0; row < numRows; ++row)
        {
            //the number of columns we have before user edits columns
            const auto num_cols_i32 = static_cast<std::int32_t>(data[row].size());
            for (auto col = num_cols_i32; col > numCols; --col)
            {
                data[row].pop_back();
            }
        }

     }

}

void WindowClass::DrawIoButtons()
{

}

void WindowClass::DrawTable()
{
    //adding a row
    //removing a row
    //adding a column
    //removing a column
}

void WindowClass::DrawSavePopup()
{
    const auto esc_pressed = ImGui::IsKeyPressed(ImGuiKey_Escape);

    SetPopupLayout();

    if (ImGui::BeginPopupModal("Save File", nullptr, popUpFlags))
    {
        ImGui::InputText("Filename", filenameBuffer, sizeof(filenameBuffer));

        if (ImGui::Button("Save", popUpButtonSize))
        {
            SaveToCsvFile(filenameBuffer);
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel", popUpButtonSize) || esc_pressed)
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void WindowClass::DrawLoadPopup()
{
    const auto esc_pressed = ImGui::IsKeyPressed(ImGuiKey_Escape);

    SetPopupLayout();

    if (ImGui::BeginPopupModal("Load File", nullptr, popUpFlags))
    {
        ImGui::InputText("Filename", filenameBuffer, sizeof(filenameBuffer));

        if (ImGui::Button("Load", popUpButtonSize))
        {
            LoadFromCsvFile(filenameBuffer);
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel", popUpButtonSize) || esc_pressed)
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void WindowClass::DrawValuePopup(const int row, const int col)
{
    const auto esc_pressed =
        ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape));

    SetPopupLayout();
    if (ImGui::BeginPopupModal("Save File", nullptr, popUpFlags))
    {
        ImGui::InputText("Filename", filenameBuffer, sizeof(filenameBuffer));

        if (ImGui::Button("Save", popUpButtonSize))
        {
            SaveToCsvFile(filenameBuffer);
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel", popUpButtonSize) || esc_pressed)
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void WindowClass::SaveToCsvFile(std::string_view filename)
{

}

void WindowClass::LoadFromCsvFile(std::string_view filename)
{

}

template <typename T>
void WindowClass::PlotCellValue(std::string_view formatter, const T value)
{

}

void WindowClass::SetPopupLayout()
{

    ImGui::SetNextWindowSize(popUpSize);
    ImGui::SetNextWindowPos(popUpPos);

}

void render(WindowClass &window_obj)

{
    window_obj.Draw("Label");
}
