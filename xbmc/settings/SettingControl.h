/*
 *      Copyright (C) 2013 Team XBMC
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "settings/lib/ISettingControl.h"
#include "settings/lib/ISettingControlCreator.h"

#define SETTING_XML_ELM_CONTROL_FORMATLABEL "formatlabel"
#define SETTING_XML_ELM_CONTROL_HIDDEN "hidden"
#define SETTING_XML_ELM_CONTROL_VERIFYNEW "verifynew"
#define SETTING_XML_ELM_CONTROL_HEADING "heading"
#define SETTING_XML_ELM_CONTROL_HIDEVALUE "hidevalue"
#define SETTING_XML_ELM_CONTROL_MULTISELECT "multiselect"
#define SETTING_XML_ELM_CONTROL_POPUP "popup"
#define SETTING_XML_ELM_CONTROL_FORMATVALUE "value"
#define SETTING_XML_ATTR_SHOW_MORE "more"
#define SETTING_XML_ATTR_SHOW_DETAILS "details"
#define SETTING_XML_ATTR_SEPARATOR_POSITION "separatorposition"
#define SETTING_XML_ATTR_HIDE_SEPARATOR "hideseparator"

class CVariant;

class CSettingControlCreator : public ISettingControlCreator
{
public:
  // implementation of ISettingControlCreator
  std::shared_ptr<ISettingControl> CreateControl(const std::string &controlType) const override;

protected:
  CSettingControlCreator() = default;
  ~CSettingControlCreator() override = default;
};

class CSettingControlCheckmark : public ISettingControl
{
public:
  CSettingControlCheckmark()
  {
    m_format = "boolean";
  }
  ~CSettingControlCheckmark() override = default;

  // implementation of ISettingControl
  std::string GetType() const override { return "toggle"; }
  bool SetFormat(const std::string &format) override;
};

class CSettingControlFormattedRange : public ISettingControl
{
public:
  ~CSettingControlFormattedRange() override = default;

  bool Deserialize(const TiXmlNode *node, bool update = false) override;

  int GetFormatLabel() const { return m_formatLabel; }
  void SetFormatLabel(int formatLabel) { m_formatLabel = formatLabel; }
  const std::string& GetFormatString() const { return m_formatString; }
  void SetFormatString(const std::string &formatString) { m_formatString = formatString; }
  int GetMinimumLabel() const { return m_minimumLabel; }
  void SetMinimumLabel(int minimumLabel) { m_minimumLabel = minimumLabel; }

protected:
  CSettingControlFormattedRange() = default;

  int m_formatLabel = -1;
  std::string m_formatString = "%i";
  int m_minimumLabel = -1;
};

class CSettingControlSpinner : public CSettingControlFormattedRange
{
public:
  CSettingControlSpinner() = default;
  ~CSettingControlSpinner() override = default;

  // implementation of ISettingControl
  std::string GetType() const override { return "spinner"; }

  // specialization of CSettingControlFormattedRange
  bool SetFormat(const std::string &format) override;
};

class CSettingControlEdit : public ISettingControl
{
public:
  CSettingControlEdit()
  {
    m_delayed = true;
  }
  ~CSettingControlEdit() override = default;

  // implementation of ISettingControl
  std::string GetType() const override { return "edit"; }
  bool Deserialize(const TiXmlNode *node, bool update = false) override;
  bool SetFormat(const std::string &format) override;

  bool IsHidden() const { return m_hidden; }
  void SetHidden(bool hidden) { m_hidden = hidden; }
  bool VerifyNewValue() const { return m_verifyNewValue; }
  void SetVerifyNewValue(bool verifyNewValue) { m_verifyNewValue = verifyNewValue; }
  int GetHeading() const { return m_heading; }
  void SetHeading(int heading) { m_heading = heading; }

protected:
  bool m_hidden = false;
  bool m_verifyNewValue = false;
  int m_heading = -1;
};

class CSettingControlButton : public ISettingControl
{
public:
  CSettingControlButton() = default;
  ~CSettingControlButton() override = default;

  // implementation of ISettingControl
  std::string GetType() const override { return "button"; }
  bool Deserialize(const TiXmlNode *node, bool update = false) override;
  bool SetFormat(const std::string &format) override;

  int GetHeading() const { return m_heading; }
  void SetHeading(int heading) { m_heading = heading; }
  bool HideValue() const { return m_hideValue; }
  void SetHideValue(bool hideValue) { m_hideValue = hideValue; }

  bool ShowAddonDetails() const { return m_showAddonDetails; }
  void SetShowAddonDetails(bool showAddonDetails) { m_showAddonDetails = showAddonDetails; }
  bool ShowInstalledAddons() const { return m_showInstalledAddons; }
  void SetShowInstalledAddons(bool showInstalledAddons) { m_showInstalledAddons = showInstalledAddons; }
  bool ShowInstallableAddons() const { return m_showInstallableAddons; }
  void SetShowInstallableAddons(bool showInstallableAddons) { m_showInstallableAddons = showInstallableAddons; }
  bool ShowMoreAddons() const { return !m_showInstallableAddons && m_showMoreAddons; }
  void SetShowMoreAddons(bool showMoreAddons) { m_showMoreAddons = showMoreAddons; }

  bool UseImageThumbs() const { return m_useImageThumbs; }
  void SetUseImageThumbs(bool useImageThumbs) { m_useImageThumbs = useImageThumbs; }
  bool UseFileDirectories() const { return m_useFileDirectories; }
  void SetUseFileDirectories(bool useFileDirectories) { m_useFileDirectories = useFileDirectories; }

  bool HasActionData() const { return !m_actionData.empty(); }
  const std::string& GetActionData() const { return m_actionData; }
  void SetActionData(const std::string& actionData) { m_actionData = actionData; }

  bool CloseDialog() const { return m_closeDialog; }
  void SetCloseDialog(bool closeDialog) { m_closeDialog = closeDialog; }

protected:
  int m_heading = -1;
  bool m_hideValue = false;

  bool m_showAddonDetails = true;
  bool m_showInstalledAddons = true;
  bool m_showInstallableAddons = false;
  bool m_showMoreAddons = true;

  bool m_useImageThumbs = false;
  bool m_useFileDirectories = false;

  std::string m_actionData;
  bool m_closeDialog = false;
};

class CSetting;
using SettingControlListValueFormatter = std::string (*)(std::shared_ptr<const CSetting> setting);

class CSettingControlList : public CSettingControlFormattedRange
{
public:
  CSettingControlList() = default;
  ~CSettingControlList() override = default;

  // implementation of ISettingControl
  std::string GetType() const override { return "list"; }

  // specialization of CSettingControlFormattedRange
  bool Deserialize(const TiXmlNode *node, bool update = false) override;
  bool SetFormat(const std::string &format) override;

  int GetHeading() const { return m_heading; }
  void SetHeading(int heading) { m_heading = heading; }
  bool CanMultiSelect() const { return m_multiselect; }
  void SetMultiSelect(bool multiselect) { m_multiselect = multiselect; }
  bool HideValue() const { return m_hideValue; }
  void SetHideValue(bool hideValue) { m_hideValue = hideValue; }

  SettingControlListValueFormatter GetFormatter() const { return m_formatter; }
  void SetFormatter(SettingControlListValueFormatter formatter) { m_formatter = formatter; }

protected:
  int m_heading = -1;
  bool m_multiselect = false;
  bool m_hideValue = false;
  SettingControlListValueFormatter m_formatter = nullptr;
};

class CSettingControlSlider;
using SettingControlSliderFormatter = std::string (*)(std::shared_ptr<const CSettingControlSlider> control, const CVariant &value, const CVariant &minimum, const CVariant &step, const CVariant &maximum);

class CSettingControlSlider : public ISettingControl
{
public:
  CSettingControlSlider() = default;
  ~CSettingControlSlider() override = default;

  // implementation of ISettingControl
  std::string GetType() const override { return "slider"; }
  bool Deserialize(const TiXmlNode *node, bool update = false) override;
  bool SetFormat(const std::string &format) override;

  int GetHeading() const { return m_heading; }
  void SetHeading(int heading) { m_heading = heading; }
  bool UsePopup() const { return m_popup; }
  void SetPopup(bool popup) { m_popup = popup; }
  int GetFormatLabel() const { return m_formatLabel; }
  void SetFormatLabel(int formatLabel) { m_formatLabel = formatLabel; }
  const std::string& GetFormatString() const { return m_formatString; }
  void SetFormatString(const std::string &formatString) { m_formatString = formatString; }

  SettingControlSliderFormatter GetFormatter() const { return m_formatter; }
  void SetFormatter(SettingControlSliderFormatter formatter) { m_formatter = formatter; }

protected:
  int m_heading = -1;
  bool m_popup = false;
  int m_formatLabel = -1;
  std::string m_formatString = "%i";
  SettingControlSliderFormatter m_formatter = nullptr;
};

class CSettingControlRange : public ISettingControl
{
public:
  CSettingControlRange() = default;
  ~CSettingControlRange() override = default;

  // implementation of ISettingControl
  std::string GetType() const override { return "range"; }
  bool Deserialize(const TiXmlNode *node, bool update = false) override;
  bool SetFormat(const std::string &format) override;

  int GetFormatLabel() const { return m_formatLabel; }
  void SetFormatLabel(int formatLabel) { m_formatLabel = formatLabel; }
  int GetValueFormatLabel() const { return m_valueFormatLabel; }
  void SetValueFormatLabel(int valueFormatLabel) { m_valueFormatLabel = valueFormatLabel; }
  const std::string& GetValueFormat() const { return m_valueFormat; }
  void SetValueFormat(const std::string &valueFormat) { m_valueFormat = valueFormat; }

protected:
  int m_formatLabel = 21469;
  int m_valueFormatLabel = -1;
  std::string m_valueFormat = "%s";
};

class CSettingControlTitle : public ISettingControl
{
public:
  CSettingControlTitle() = default;
  ~CSettingControlTitle() override = default;

  // implementation of ISettingControl
  std::string GetType() const override { return "title"; }
  bool Deserialize(const TiXmlNode *node, bool update = false) override;

  bool IsSeparatorHidden() const { return m_separatorHidden; }
  void SetSeparatorHidden(bool hidden) { m_separatorHidden = hidden; }
  bool IsSeparatorBelowLabel() const { return m_separatorBelowLabel; }
  void SetSeparatorBelowLabel(bool below) { m_separatorBelowLabel = below; }

protected:
  bool m_separatorHidden = false;
  bool m_separatorBelowLabel = true;
};

class CSettingControlLabel : public ISettingControl
{
public:
  CSettingControlLabel();
  ~CSettingControlLabel() override = default;

  // implementation of ISettingControl
  std::string GetType() const override { return "label"; }
};
