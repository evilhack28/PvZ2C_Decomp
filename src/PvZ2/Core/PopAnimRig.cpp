//
//  PopAnimRig.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-09-25.
//

#include "SexyAppFramework/Common.h"

#include "PopAnimRig.h"
#include "SexyAppFramework/PopAnim.h"
#include "ScaledApp.h"
#include "PopAnimUtils.h"
#include "AudioMgr.h"
#include "BoardEntity.h"
#include "LawnApp.h"
#include "ResourceHelpers.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/RenderEffect.h"
#include "SexyAppFramework/SexyVector.h"
#include <random>
#include <deque>
#include <queue>
#include <set>

class GlobalAnimCountCache
{
public:
	unsigned char GetAnimCountForLabel(Sexy::PopAnim* i_pam, const std::string& i_label);
};

static CachedResourcePtr<RenderEffectDefinition> g_colorizeEffect("EFFECT_COLORIZE_OVERLAY");
static CachedResourcePtr<RenderEffectDefinition> g_multiplicativeEffect("EFFECT_MULTIPLICATIVE_OVERLAY");
static CachedResourcePtr<RenderEffectDefinition> g_desaturateEffect("EFFECT_DESATURATE");
static CachedResourcePtr<RenderEffectDefinition> g_goldEffect("EFFECT_GOLDLIZATION");

static GlobalAnimCountCache g_animCountCache;

void getTransform(const Sexy::PASpriteDef* i_spriteDef, Sexy::PAFrame* i_frame, int i_index, Sexy::PATransform* o_transform);

void PopAnimRig::onAnimStopped()
{
}

void PopAnimRig::onAnimInterrupted()
{
}

void PopAnimRig::onAnimSequenceContinued()
{
}

void PopAnimRig::onUpdate()
{
}

#include "ReflectionBuilder.h"

RT_CLASS_IMPLEMENT(PopAnimRig);

void PopAnimRig::StaticClassInit()
{
	REFLECTION_CLASSBUILDER_BEGIN(PopAnimRig);
	REFLECTION_CLASSBUILDER_RTCLASS_BIND;

		REFLECTION_CLASSBUILDER_ANCESTOR(GameObject);

		REFLECTION_CLASSBUILDER_FIELD(std::string, m_activeAnimBaseLabel);
		REFLECTION_CLASSBUILDER_FIELD(std::vector<int>, m_animRandomDistribution);
		REFLECTION_CLASSBUILDER_FIELD(Color, m_shaderOverrideColor);
		REFLECTION_CLASSBUILDER_FIELD(float, m_saturation);
	REFLECTION_CLASSBUILDER_END(PopAnimRig);
}

void PopAnimRig::onPostDraw(Graphics* i_arg)
{
}

void PopAnimRig::onPostPlayCalled()
{
}

void PopAnimRig::onPreDraw(Graphics* i_arg)
{
}

/////////////// Accessors ///////////////

void PopAnimRig::SetDisabled(bool i_state)
{
	m_disabled = i_state;
}

bool PopAnimRig::GetIsDisabled() const
{
	return m_disabled;
}

void PopAnimRig::SetSaturation(float i_state)
{
	m_saturation = i_state;
}

bool PopAnimRig::GetMirrorX() const
{
	return m_mirrorX;
}

void PopAnimRig::SetPAMColor(const Color& i_newColor)
{
	m_pam->SetPAMColor(i_newColor);
}

void PopAnimRig::ClearShaderOverrideColor()
{
	m_useShaderOverrideColor = false;
}

void PopAnimRig::ClearMultiplicativeOverlayColor()
{
	m_useMultiplicativeOverlayColor = false;
}

float PopAnimRig::GetDrawScale() const
{
	return m_pam->mDrawScale;
}

void PopAnimRig::SetDrawScale(const float i_drawScale)
{
	m_pam->mDrawScale = i_drawScale;
}

bool PopAnimRig::IsPlayingAnything() const
{
	return m_pam->mAnimRunning;
}

float PopAnimRig::ConvertPAMCoordinateToLogicSpace(float i_value)
{
	return INV_S(i_value * m_pam->mImgScale);
}

float PopAnimRig::ConvertPAMCoordinateToScreenSpace(float i_value)
{
	return i_value * m_pam->mImgScale;
}

bool PopAnimRig::IsAnimActive(AnimHandle i_animHandle) const
{
	return m_activeAnim == i_animHandle;
}

void PopAnimRig::SetShaderOverrideColor(const Color& i_newColor)
{
	m_shaderOverrideColor = i_newColor;
	m_useShaderOverrideColor = true;
}

void PopAnimRig::SetMultiplicativeOverlayColor(const Color& i_newColor)
{
	m_multiplicativeOverlayColor = i_newColor;
	m_useMultiplicativeOverlayColor = true;
}

void PopAnimRig::SetAnimRateOverride(float i_multiplier)
{
	m_pam->mAnimRate = (int)(i_multiplier * m_pam->mMainAnimDef->mMainSpriteDef->mAnimRate);
}

void PopAnimRig::ClearAnimRateOverride()
{
	m_pam->mAnimRate = (int)m_pam->mMainAnimDef->mMainSpriteDef->mAnimRate;
}

void PopAnimRig::SetMirrorX(bool i_mirror)
{
	m_mirrorX = i_mirror;
	m_pam->mTransform.m00 = i_mirror ? -1.0f : 1.0f;
}

bool PopAnimRig::DoesAnimationLabelExist(const std::string& i_frameLabel)
{
	return m_pam->GetLabelFrame(i_frameLabel) > 0;
}

void PopAnimRig::SetForceAdditive(bool i_additive)
{
	getPAM()->mAdditive = i_additive;
}

void PopAnimRig::SetPaused(bool i_state)
{
	getPAM()->mPaused = i_state;
}

Color PopAnimRig::GetPAMColor() const
{
	return m_pam->mColor;
}

bool PopAnimRig::IsAnimFinished(AnimHandle i_animHandle) const
{
	return !IsAnimActive(i_animHandle) || !IsPlayingAnything();
}

void PopAnimRig::onPopAnimCommand(pvztime_t i_atTime, const std::string& i_command, const std::string& i_param)
{
	if (i_command == "pause")
		m_pam->mPaused = true;
}

pvztime_t PopAnimRig::CalcAnimLengthSeconds(const std::string& i_frameLabel)
{
	int length = CalcAnimLength(i_frameLabel);
	if (length == -1)
		return 0.0f;
	return (float)length / (float)m_pam->mAnimRate;
}

PopAnimRig* PopAnimRig::CreateRigOutsideTable(const PopAnim* i_pam, RtClass* i_class)
{
	PopAnimRig* rig = GameObject::Create(i_class, PVZDB::TABLE_INVALID)->CastChecked<PopAnimRig>();
	rig->popAnimInitialize(i_pam->Duplicate(), true);
	return rig;
}

PopAnimRig* PopAnimRig::CreateRig(const PopAnim* i_pam, RtClass* i_class)
{
	PopAnimRig* rig = GameObject::Create(i_class, PVZDB::TABLE_POPANIMRIGS)->CastChecked<PopAnimRig>();
	rig->popAnimInitialize(i_pam->Duplicate(), true);
	return rig;
}

void PopAnimRig::onPopAnimInitialized()
{
	m_properlyInitialized = true;
}

bool PopAnimRig::IsAnimStringActive(const std::string& i_animName)
{
	return m_activeAnimBaseLabel == i_animName;
}

bool PopAnimRig::hasColorizeOverlay()
{
	return m_useShaderOverrideColor;
}

bool PopAnimRig::hasMultiplicativeOverlay()
{
	return m_useMultiplicativeOverlayColor;
}

void PopAnimRig::UpdateAnim(pvztime_t i_t, pvztime_t i_dt)
{
	VSyncPopAnimUpdate(m_pam, &m_virtualStepTime, i_t, i_dt);
	onUpdate();
}

void PopAnimRig::SetRenderTransform(const SexyTransform2D& i_transform)
{
	m_pam->mTransform = i_transform;
	if (m_mirrorX)
		m_pam->mTransform.m00 = -m_pam->mTransform.m00;
}

bool PopAnimRig::SetLayerVisibility(const std::string& i_layerName, bool i_visible)
{
	return getPAM()->mMainSpriteInst->SetSpriteVisibility(i_layerName, i_visible);
}

void PopAnimRig::Draw(Graphics* i_g, const SexyTransform2D& i_transform)
{
	SetRenderTransform(i_transform);
	Draw(i_g);
}

int PopAnimRig::CalcAnimLength(const std::string& i_frameLabel)
{
	int start = -1;
	int end = -1;
	m_pam->mMainSpriteInst->mDef->GetLabelFrameRange(i_frameLabel, start, end);
	if (start < 0)
		return -1;
	return end >= 0 ? end - start : -1;
}

void PopAnimRig::fireInterrupts(const std::string& i_labelToPlay, int i_lastPlayedVariation)
{
	if (m_activeAnim == ANIMHANDLE_NONE || !IsPlayingAnything())
		return;
	onAnimInterrupted();
}

const float PopAnimRig::GetCurrentFrameInAnimation() const
{
	int labelFrame = m_pam->mMainSpriteInst->mDef->GetLabelFrame(m_activeAnimBaseLabel);
	if (labelFrame < 0)
		return 0.0f;
	return m_pam->mMainSpriteInst->mFrameNum - labelFrame;
}

std::string PopAnimRig::CalcVariationLabelName(const std::string& i_animLabelBase, int i_variationIndex) const
{
	if (i_variationIndex == 0)
		return i_animLabelBase;
	int n = 2;
	if (i_variationIndex != 1)
	{
		n = i_variationIndex + 1;
		if (n == 0)
			return i_animLabelBase;
	}
	return StrFormat("%s%d", i_animLabelBase.c_str(), n);
}

std::string PopAnimRig::CalcPlayingAnimLabelName() const
{
	return CalcVariationLabelName(m_activeAnimBaseLabel, m_activeAnimLastPlayedVariation);
}

void PopAnimRig::ClearPopAnimCommandDelegate()
{
	m_onPopAnimCommand = PopAnimCommandDelegate();
	m_serialOnPopAnimCommand = PopAnimCommandReflectionDelegate();
}

bool PopAnimRig::CalcLayerTranslation(const std::string& i_layerName, float& o_posX, float& o_posY)
{
	float x = 0.0f;
	float y = 0.0f;
	if (getCurrentTranslation(i_layerName, x, y, NULL))
	{
		o_posX = x;
		o_posY = y;
		return true;
	}
	return false;
}

bool PopAnimRig::CalcLayerTranslation(const std::string& i_layerName, SexyVector2& o_pos)
{
	SexyVector2 pos;
	bool found = false;
	if (CalcLayerTranslation(i_layerName, pos.x, pos.y))
	{
		o_pos = pos;
		found = true;
	}
	return found;
}

void PopAnimRig::AdvanceToLastFrameInAnimation()
{
	int start = -1;
	int end = -1;
	m_pam->mMainSpriteInst->mDef->GetLabelFrameRange(m_activeAnimBaseLabel, start, end);
	if (start >= 0 && end >= 0)
		m_pam->mMainSpriteInst->mFrameNum = end - 1;
}

void PopAnimRig::SetCurrentFrameInAnimation(const float i_animationFrame)
{
	int start = -1;
	int end = -1;
	float f = i_animationFrame;
	m_pam->mMainSpriteInst->mDef->GetLabelFrameRange(m_activeAnimBaseLabel, start, end);
	if (start >= 0 && end >= 0)
	{
		float frame = std::max((float)start, std::min(f + start, (float)end));
		m_pam->mMainSpriteInst->mFrameNum = frame;
	}
}

void PopAnimRig::RandomizeCurrentAnimFrame()
{
	std::string label = CalcPlayingAnimLabelName();
	int start;
	int end;
	m_pam->mMainSpriteInst->mDef->GetLabelFrameRange(label, start, end);
	if (start < 0 || end < 0)
		return;
	int r = Rand(end - start);
	m_pam->mMainSpriteInst->mFrameNum = r + start;
}

SexyVector2 PopAnimRig::GetPAMSize(float fScale) const
{
	SexyVector2 size;
	if (m_pam)
	{
		float ds = m_pam->mDrawScale;
		float w = m_pam->mAnimRect.mWidth * ds;
		float h = m_pam->mAnimRect.mHeight * ds;
		size.y = h * fScale;
		size.x = w * fScale;
	}
	return size;
}

void PopAnimRig::clearPlaybackDelegates()
{
	m_onAnimStopped = AnimStoppedDelegate();
	m_onLoopingAnimContinued = LoopingAnimContinuedDelegate();
	m_serialOnAnimStopped = AnimStoppedReflectionDelegate();
	m_serialOnLoopingAnimContinued = LoopingAnimContinuedReflectionDelegate();
}

const Color PopAnimRig::getOverlayEffectsColor()
{
	Color color(Color::White);
	if (m_useShaderOverrideColor)
		return m_shaderOverrideColor;
	if (m_useMultiplicativeOverlayColor)
		color = color * m_multiplicativeOverlayColor;
	return color;
}

void PopAnimRig::SetAdditiveDraw(bool i_useAdditive)
{
	PASpriteDef* def = m_pam->mMainSpriteInst->mDef;
	for (size_t i = 0; i < def->mFrames.size(); i++)
	{
		PAFrame& frame = def->mFrames[i];
		for (int j = 0; j < (int)frame.mFrameObjectPosIndexVector.size(); j++)
			def->mObjectPosVector[frame.mFrameObjectPosIndexVector[j]].mIsAdditive = i_useAdditive;
	}
}

bool PopAnimRig::CalcLayerTransformScreenSpace(const std::string& i_layerName, SexyMatrix3& o_transform)
{
	PATransform transform;
	if (getCurrentTransformPAMSpace(i_layerName, transform, NULL))
	{
		o_transform = transform.mMatrix.GetMatrix3();
		o_transform.m02 = ConvertPAMCoordinateToScreenSpace(o_transform.m02);
		o_transform.m12 = ConvertPAMCoordinateToScreenSpace(o_transform.m12);
		return true;
	}
	return false;
}

void PopAnimRig::popAnimInitialize(PopAnim* i_pam, bool i_manageDeletion)
{
	m_pam = i_pam;
	m_pam->SetupSpriteInst("");
	m_manageDeletion = i_manageDeletion;
	m_pam->mListener = this;
	m_disabled = false;
	m_useShaderOverrideColor = false;
	m_mirrorX = false;
	m_saturation = 1.0f;
	clearPlaybackDelegates();
	ClearPopAnimCommandDelegate();
	m_properlyInitialized = false;
	onPopAnimInitialized();
}

PASpriteInst* PopAnimRig::CalcSymbolRect(const std::string& i_layerName, Sexy::Rect& o_rect)
{
	SexyTransform2D oldTransform = getPAM()->mTransform;
	SetRenderTransform(SexyTransform2D());
	getPAM()->mTransDirty = true;
	PASpriteInst* result = getSymbolRect(i_layerName, o_rect, GetPAM()->mMainSpriteInst, NULL, false);
	getPAM()->mTransform = oldTransform;
	getPAM()->mTransDirty = true;
	return result;
}

void PopAnimRig::CalcRigDrawingRect(Sexy::Rect& o_rect)
{
	SexyTransform2D oldTransform = getPAM()->mTransform;
	SetRenderTransform(SexyTransform2D());
	getPAM()->mTransDirty = true;
	getSymbolRect("never give me up", o_rect, getPAM()->mMainSpriteInst, NULL, true);
	getPAM()->mTransform = oldTransform;
	getPAM()->mTransDirty = true;
}

int PopAnimRig::selectNextVariationIndex()
{
	int index = -1;
	switch (m_activeAnimSelectMethod)
	{
	case SELECT_EXACT:
		index = m_activeAnimLastPlayedVariation;
		break;
	case SELECT_INORDER:
		index = CalcAnimVariationCount(m_activeAnimBaseLabel) > m_activeAnimLastPlayedVariation + 1 ? m_activeAnimLastPlayedVariation + 1 : 0;
		break;
	case SELECT_RANDOM_INDEX:
		index = Rand(CalcAnimVariationCount(m_activeAnimBaseLabel));
		break;
	case SELECT_RANDOM_INDEX_NOREPEAT:
		{
			int count = CalcAnimVariationCount(m_activeAnimBaseLabel);
			if (count == 1)
			{
				index = m_activeAnimLastPlayedVariation;
			}
			else
			{
				index = Rand(count - 1);
				if (index >= m_activeAnimLastPlayedVariation)
					index++;
			}
		}
		break;
	case SELECT_RANDOM_DISTRIBUTION:
		{
			std::discrete_distribution<int> distribution(m_animRandomDistribution.begin(), m_animRandomDistribution.end());
			index = distribution(GetRandEngine());
		}
		break;
	}
	return index;
}

int PopAnimRig::CalcAnimVariationCount(const std::string& i_animLabelBase)
{
	return g_animCountCache.GetAnimCountForLabel(m_pam, i_animLabelBase);
}

PopAnimRig::PopAnimRig()
{
	m_pam = NULL;
	m_activeAnimPlayStyle = PLAY_ONCE;
	m_activeAnim = ANIMHANDLE_NONE;
	m_activeAnimLastPlayedVariation = -1;
	m_activeAnimSelectMethod = SELECT_EXACT;
	m_activeAnimSeqEndCount = 0;
	m_manageDeletion = false;
	m_useMultiplicativeOverlayColor = false;
	m_disabled = false;
	m_useShaderOverrideColor = false;
	m_mirrorX = false;
	m_saturation = 1.0f;
	m_virtualStepTime = PVZ_EOT();
	m_properlyInitialized = false;
	m_goldLization = false;
}

PopAnimRig::~PopAnimRig()
{
	if (m_manageDeletion && m_pam)
	{
		delete m_pam;
		m_pam = NULL;
	}
}

void PopAnimRig::PopAnimCommand(int i_id, const std::string& i_command, const std::string& i_param)
{
	if (m_onPopAnimCommand)
		m_onPopAnimCommand(CalcVariationLabelName(m_activeAnimBaseLabel, m_activeAnimLastPlayedVariation), m_virtualStepTime, i_command, i_param);
	if (m_serialOnPopAnimCommand)
		m_serialOnPopAnimCommand.GetDelegate()(CalcVariationLabelName(m_activeAnimBaseLabel, m_activeAnimLastPlayedVariation), m_virtualStepTime, i_command, i_param);
	onPopAnimCommand(m_virtualStepTime, i_command, i_param);
}

AnimHandle PopAnimRig::Play(const std::string& i_animLabel, AnimPlayStyle i_playStyle, AnimSelectionMethod i_select, const std::vector<int> i_randomDistribution)
{
	std::string labelToPlay;
	if (selectVariation(i_animLabel, i_select, labelToPlay, m_activeAnimLastPlayedVariation, i_randomDistribution))
	{
		int variation = m_activeAnimLastPlayedVariation;
		if (m_pam->Play(labelToPlay, true))
		{
			fireInterrupts(labelToPlay, variation);
			m_activeAnimPlayStyle = i_playStyle;
			m_activeAnimSelectMethod = i_select;
			m_activeAnim = (AnimHandle)(m_activeAnim + 1);
			m_activeAnimBaseLabel = i_animLabel;
			m_activeAnimSeqEndCount = 0;
			m_animRandomDistribution.clear();
			if (i_select == SELECT_RANDOM_DISTRIBUTION)
				m_animRandomDistribution = i_randomDistribution;
			onPostPlayCalled();
			return m_activeAnim;
		}
	}
	return ANIMHANDLE_NONE;
}

bool PopAnimRig::selectVariation(const std::string& i_animLabel, AnimSelectionMethod i_select, std::string& o_labelToPlay, int& o_variationIndex, const std::vector<int> i_randomDistribution)
{
	switch (i_select)
	{
	case SELECT_EXACT:
	case SELECT_INORDER:
		o_labelToPlay = i_animLabel;
		o_variationIndex = 0;
		break;
	case SELECT_RANDOM_INDEX:
	case SELECT_RANDOM_INDEX_NOREPEAT:
		{
			int count = CalcAnimVariationCount(i_animLabel);
			if (count == 0)
				return false;
			int index = Rand(count);
			o_labelToPlay = CalcVariationLabelName(i_animLabel, index);
			o_variationIndex = index;
		}
		break;
	case SELECT_RANDOM_DISTRIBUTION:
		{
			std::discrete_distribution<int> distribution(i_randomDistribution.begin(), i_randomDistribution.end());
			int index = distribution(GetRandEngine());
			o_labelToPlay = CalcVariationLabelName(i_animLabel, index);
			o_variationIndex = index;
		}
		break;
	}
	return true;
}

void PopAnimRig::PopAnimStopped(int i_id)
{
	if (m_activeAnimPlayStyle == PLAY_ONCE)
	{
		if (m_onAnimStopped)
			m_onAnimStopped(CalcVariationLabelName(m_activeAnimBaseLabel, m_activeAnimLastPlayedVariation));
		if (m_serialOnAnimStopped)
			m_serialOnAnimStopped.GetDelegate()(CalcVariationLabelName(m_activeAnimBaseLabel, m_activeAnimLastPlayedVariation));
		onAnimStopped();
	}
	else
	{
		int newIndex = selectNextVariationIndex();
		std::string labelToPlay = CalcVariationLabelName(m_activeAnimBaseLabel, newIndex);
		m_pam->Play(labelToPlay, true);
		int oldIndex = m_activeAnimLastPlayedVariation;
		m_activeAnimLastPlayedVariation = newIndex;
		m_activeAnimSeqEndCount++;
		onAnimSequenceContinued();
		if (m_onLoopingAnimContinued)
			m_onLoopingAnimContinued(CalcVariationLabelName(m_activeAnimBaseLabel, oldIndex), labelToPlay, m_activeAnimSeqEndCount);
		if (m_serialOnLoopingAnimContinued)
			m_serialOnLoopingAnimContinued.GetDelegate()(CalcVariationLabelName(m_activeAnimBaseLabel, oldIndex), labelToPlay, m_activeAnimSeqEndCount);
	}
}

PASpriteInst* PopAnimRig::GetTransformFromPAM(const PopAnim* i_PAM, const std::string i_layerName, int i_frameNumber, SexyMatrix3& o_transform, PASpriteInst* i_spriteInst)
{
	if (i_spriteInst == NULL)
		i_spriteInst = i_PAM->mMainSpriteInst;
	PASpriteDef* spriteDef = i_PAM->mMainAnimDef->mMainSpriteDef;
	PAFrame& frame = spriteDef->mFrames[i_frameNumber];
	int i = 0;
	int numObjects = frame.mFrameObjectPosIndexVector.size();
	while (i < numObjects)
	{
		PAObjectPos& objPos = spriteDef->mObjectPosVector[frame.mFrameObjectPosIndexVector[i]];
		if (objPos.mIsSprite)
		{
			if (i_PAM->mMainAnimDef->mSpriteDefVector[objPos.mResNum].mExportName == i_layerName)
			{
				PATransform transform;
				getTransform(i_PAM->mMainAnimDef->mMainSpriteDef, &frame, i, &transform);
				o_transform = o_transform * transform.mMatrix.GetMatrix3();
				return i_spriteInst;
			}
		}
		i++;
	}
	return NULL;
}

PASpriteInst* PopAnimRig::getCurrentTranslation(const std::string& i_layerName, float& i_posX, float& i_posY, PASpriteInst* i_spriteInst)
{
	PASpriteInst* spriteInst = i_spriteInst;
	if (spriteInst == NULL)
		spriteInst = m_pam->mMainSpriteInst;
	PAFrame& frame = spriteInst->mDef->mFrames[(int)spriteInst->mFrameNum];
	for (int i = 0; i < (int)frame.mFrameObjectPosIndexVector.size(); i++)
	{
		PAObjectPos& objPos = spriteInst->mDef->mObjectPosVector[frame.mFrameObjectPosIndexVector[i]];
		PASpriteInst* result;
		if (objPos.mIsSprite)
		{
			if (m_pam->mMainAnimDef->mSpriteDefVector[objPos.mResNum].mExportName == i_layerName)
				goto found;
			result = getCurrentTranslation(i_layerName, i_posX, i_posY, spriteInst->mChildren[objPos.mObjectNum].mSpriteInst);
			if (result)
			{
				if (i_spriteInst)
					return result;
found:
				PATransform transform;
				Color color;
				m_pam->CalcObjectPos(spriteInst, &objPos, &transform, &color);
				i_posX += ConvertPAMCoordinateToLogicSpace(transform.mMatrix.m02);
				i_posY += ConvertPAMCoordinateToLogicSpace(transform.mMatrix.m12);
				return spriteInst;
			}
		}
	}
	return NULL;
}

PASpriteInst* PopAnimRig::getCurrentTransformPAMSpace(const std::string& i_layerName, PATransform& o_transform, PASpriteInst* i_spriteInst)
{
	PASpriteInst* spriteInst = i_spriteInst;
	if (spriteInst == NULL)
		spriteInst = m_pam->mMainSpriteInst;
	PAFrame& frame = spriteInst->mDef->mFrames[(int)spriteInst->mFrameNum];
	for (int i = 0; i < (int)frame.mFrameObjectPosIndexVector.size(); i++)
	{
		PAObjectPos& objPos = spriteInst->mDef->mObjectPosVector[frame.mFrameObjectPosIndexVector[i]];
		PASpriteInst* result;
		if (objPos.mIsSprite)
		{
			if (m_pam->mMainAnimDef->mSpriteDefVector[objPos.mResNum].mExportName == i_layerName)
				goto found;
			result = getCurrentTransformPAMSpace(i_layerName, o_transform, spriteInst->mChildren[objPos.mObjectNum].mSpriteInst);
			if (result)
			{
				if (i_spriteInst)
					return result;
found:
				PATransform transform;
				Color color;
				m_pam->CalcObjectPos(spriteInst, &objPos, &transform, &color);
				o_transform = transform.TransformSrc(o_transform);
				return spriteInst;
			}
		}
	}
	return NULL;
}

void PopAnimRig::PopAnimPlaySample(const std::string& i_sampleName, int i_pan, double i_volume, double i_numSteps)
{
	if (gLawnApp->GetSfxVolume() <= 0.0)
		return;
	if (m_audioObject.IsValid())
		m_audioObject->PlayPositionalSound(i_sampleName, 0.0f);
	else
		AudioMgr::GetInstancePtr()->SendEvent(i_sampleName, NULL);
}

void PopAnimRig::DrawReplaceLayerWithImage(Graphics* i_g, const SexyTransform2D& i_transform, const std::string& i_layerName, Image* i_replaceImage)
{
	SetRenderTransform(i_transform);
	DrawReplaceLayerWithImage(i_g, i_layerName, i_replaceImage);
}

void PopAnimRig::internalDrawSprite(Graphics* i_g, PASpriteInst* i_spriteToDrawInst, PASpriteInst* i_spriteInst, PATransform* i_parentTransform)
{
	PATransform transform;
	PAFrame& frame = i_spriteInst->mDef->mFrames[(int)i_spriteInst->mFrameNum];
	for (int i = 0; i < (int)frame.mFrameObjectPosIndexVector.size(); i++)
	{
		PAObjectPos& objPos = i_spriteInst->mDef->mObjectPosVector[frame.mFrameObjectPosIndexVector[i]];
		if (objPos.mIsSprite)
		{
			PASpriteInst* childInst = i_spriteInst->mChildren[objPos.mObjectNum].mSpriteInst;
			transform.mMatrix = getPAM()->mTransform * childInst->mCurTransform.mMatrix.GetMatrix3();
			if (i_spriteToDrawInst == childInst)
				getPAM()->DrawSprite(i_g, i_spriteToDrawInst, &transform, getPAM()->mColor, false);
			else
				internalDrawSprite(i_g, i_spriteToDrawInst, childInst, &transform);
		}
	}
}

void PopAnimRig::DebugPrintLayerNames()
{
	std::deque<PASpriteInst*> spriteQueue;
	std::set<std::string> layerNames;
	spriteQueue.push_back(m_pam->mMainSpriteInst);
	while (!spriteQueue.empty())
	{
		PASpriteInst* spriteInst = spriteQueue.front();
		spriteQueue.pop_front();
		const std::string& exportName = spriteInst->mDef->mExportName;
		if (exportName.size() != 0)
			layerNames.insert(exportName);
		std::vector<PAObjectInst>::iterator it = spriteInst->mChildren.begin();
		std::vector<PAObjectInst>::iterator end = spriteInst->mChildren.end();
		for (; it != end; ++it)
		{
			if ((*it).mSpriteInst != NULL)
				spriteQueue.push_back((*it).mSpriteInst);
		}
	}
	OutputDebugStrF("Layer names for %s:\n", m_pam->mMainAnimDef->mLoadedPamFile.c_str());
	std::set<std::string>::iterator it = layerNames.begin();
	std::set<std::string>::iterator end = layerNames.end();
	for (; it != end; ++it)
		OutputDebugStrF("%s\n", (*it).c_str());
}

PASpriteInst* PopAnimRig::getSymbolRect(const std::string& i_layerName, Sexy::Rect& o_rect, PASpriteInst* i_spriteInst, PATransform* i_parentTransform, bool layerFound)
{
	if (getPAM()->mTransDirty)
	{
		getPAM()->UpdateTransforms();
		getPAM()->mTransDirty = false;
	}
	PASpriteInst* result = NULL;
	PATransform objTransform;
	PAFrame& frame = i_spriteInst->mDef->mFrames[(int)i_spriteInst->mFrameNum];
	for (int i = 0; i < (int)frame.mFrameObjectPosIndexVector.size(); i++)
	{
		PAObjectPos& objPos = i_spriteInst->mDef->mObjectPosVector[frame.mFrameObjectPosIndexVector[i]];
		if (objPos.mIsSprite)
			objTransform = i_spriteInst->mChildren[objPos.mObjectNum].mSpriteInst->mCurTransform;
		else
			objTransform = objPos.mTransform;
		PATransform transform;
		if (i_parentTransform == NULL || objPos.mIsSprite)
		{
			transform = objTransform;
			PATransform scaleTransform;
			scaleTransform.mMatrix.m00 = GetPAM()->mDrawScale;
			scaleTransform.mMatrix.m11 = GetPAM()->mDrawScale;
			SexyMatrix3 scaleMatrix = scaleTransform.mMatrix.GetMatrix3();
			SexyMatrix3 baseMatrix = GetPAM()->mTransform * scaleMatrix;
			SexyMatrix3 objMatrix = transform.mMatrix.GetMatrix3();
			SexyMatrix3 combined = baseMatrix * objMatrix;
			transform.mMatrix = combined;
		}
		else
		{
			transform = i_parentTransform->TransformSrc(objTransform);
		}
		if (objPos.mIsSprite)
		{
			PASpriteInst* childInst = i_spriteInst->mChildren[objPos.mObjectNum].mSpriteInst;
			if (!layerFound && childInst->mDef->mExportName == i_layerName)
			{
				getSymbolRect(i_layerName, o_rect, childInst, &transform, true);
				result = childInst;
			}
			else
			{
				PASpriteInst* found = getSymbolRect(i_layerName, o_rect, childInst, &transform, layerFound);
				if (result == NULL)
					result = found;
			}
		}
		else if (layerFound)
		{
			PAImage& image = getPAM()->mMainAnimDef->mImageVector[objPos.mResNum];
			PATransform imageTransform = image.mTransform;
			float imgScale = getPAM()->mImgScale;
			imageTransform.mMatrix.m00 *= imgScale;
			imageTransform.mMatrix.m01 *= imgScale;
			imageTransform.mMatrix.m10 *= imgScale;
			imageTransform.mMatrix.m11 *= imgScale;
			PATransform placed = transform.TransformSrc(imageTransform);
			Sexy::Rect imageRect(0, 0, image.mOrigWidth, image.mOrigHeight);
			SexyVector2 corners[4] = {
				SexyVector2(imageRect.mX, imageRect.mY),
				SexyVector2(imageRect.mX + imageRect.mWidth, imageRect.mY),
				SexyVector2(imageRect.mX + imageRect.mWidth, imageRect.mY + imageRect.mHeight),
				SexyVector2(imageRect.mX, imageRect.mY + imageRect.mHeight)
			};
			for (int c = 0; c < 4; c++)
				corners[c] = placed.mMatrix * corners[c];
			if (o_rect == Sexy::Rect())
			{
				o_rect.mX = (int)corners[0].x;
				o_rect.mY = (int)corners[1].y;
			}
			for (int c = 0; c < 4; c++)
				o_rect.ExpandToContain((int)corners[c].x, (int)corners[c].y);
		}
	}
	return result;
}

void PopAnimRig::DrawSprite(Graphics* i_g, PASpriteInst* i_spriteInst, const SexyTransform2D& i_transform)
{
	SexyTransform2D oldTransform = GetPAM()->mTransform;
	SetRenderTransform(i_transform);
	float drawScale = GetPAM()->mDrawScale;
	if (drawScale != 1.0f)
	{
		PopAnim* pam = getPAM();
		pam->mTransform.m00 *= drawScale;
		pam->mTransform.m01 *= drawScale;
		pam->mTransform.m10 *= drawScale;
		pam->mTransform.m11 *= drawScale;
	}
	if (GetPAM()->mTransDirty)
	{
		getPAM()->UpdateTransforms();
		getPAM()->mTransDirty = false;
	}
	if (hasColorizeOverlay() && i_g->Get3D())
	{
		Color overlay = getOverlayEffectsColor();
		RenderEffect* effect = i_g->Get3D()->GetEffect(g_colorizeEffect);
		effect->SetCurrentTechnique("Default", true);
		float params[4];
		params[0] = std::min(overlay.GetRed() * (1.0f / 255.0f), 255.0f);
		params[1] = std::min(overlay.GetGreen() * (1.0f / 255.0f), 255.0f);
		params[2] = std::min(overlay.GetBlue() * (1.0f / 255.0f), 255.0f);
		params[3] = std::min(overlay.GetAlpha() * (1.0f / 255.0f), 255.0f);
		effect->SetVector4("Params", params);
		for (RenderEffectAutoState state(i_g, effect, 1); state; ++state)
			internalDrawSprite(i_g, i_spriteInst, GetPAM()->mMainSpriteInst, NULL);
	}
	else
	{
		internalDrawSprite(i_g, i_spriteInst, GetPAM()->mMainSpriteInst, NULL);
	}
	getPAM()->mTransform = oldTransform;
}

void PopAnimRig::Draw(Graphics* i_g)
{
	if (m_disabled)
		return;
	onPreDraw(i_g);
	if (m_goldLization && i_g->Get3D())
	{
		RenderEffect* effect = i_g->Get3D()->GetEffect(g_goldEffect);
		effect->SetCurrentTechnique("Default", true);
		for (RenderEffectAutoState state(i_g, effect, 1); state; ++state)
			m_pam->Draw(i_g);
	}
	else if (hasColorizeOverlay() && i_g->Get3D())
	{
		Color overlay = getOverlayEffectsColor();
		RenderEffect* effect = i_g->Get3D()->GetEffect(g_colorizeEffect);
		effect->SetCurrentTechnique("Default", true);
		float params[4];
		params[0] = std::min(overlay.GetRed() * (1.0f / 255.0f), 255.0f);
		params[1] = std::min(overlay.GetGreen() * (1.0f / 255.0f), 255.0f);
		params[2] = std::min(overlay.GetBlue() * (1.0f / 255.0f), 255.0f);
		params[3] = std::min(overlay.GetAlpha() * (1.0f / 255.0f), 255.0f);
		effect->SetVector4("Params", params);
		for (RenderEffectAutoState state(i_g, effect, 1); state; ++state)
			m_pam->Draw(i_g);
	}
	else if (hasMultiplicativeOverlay() && i_g->Get3D())
	{
		Color overlay = getOverlayEffectsColor();
		RenderEffect* effect = i_g->Get3D()->GetEffect(g_multiplicativeEffect);
		effect->SetCurrentTechnique("Default", true);
		float params[4];
		params[0] = std::min(overlay.GetRed() * (1.0f / 255.0f), 255.0f);
		params[1] = std::min(overlay.GetGreen() * (1.0f / 255.0f), 255.0f);
		params[2] = std::min(overlay.GetBlue() * (1.0f / 255.0f), 255.0f);
		params[3] = std::min(overlay.GetAlpha() * (0.5f / 255.0f), 255.0f);
		effect->SetVector4("Params", params);
		for (RenderEffectAutoState state(i_g, effect, 1); state; ++state)
			m_pam->Draw(i_g);
	}
	else if (m_saturation < 1.0f && i_g->Get3D())
	{
		RenderEffect* effect = i_g->Get3D()->GetEffect(g_desaturateEffect);
		effect->SetCurrentTechnique("Default", true);
		effect->SetFloat("Saturation", m_saturation);
		for (RenderEffectAutoState state(i_g, effect, 1); state; ++state)
			m_pam->Draw(i_g);
	}
	else
	{
		m_pam->Draw(i_g);
	}
	onPostDraw(i_g);
}

void PopAnimRig::DrawReplaceLayerWithImage(Graphics* i_g, const std::string& i_layerName, Image* i_replaceImage)
{
	if (m_disabled)
		return;
	if (m_goldLization && i_g->Get3D())
	{
		RenderEffect* effect = i_g->Get3D()->GetEffect(g_goldEffect);
		effect->SetCurrentTechnique("Default", true);
		for (RenderEffectAutoState state(i_g, effect, 1); state; ++state)
			m_pam->DrawReplaceLayerWithImage(i_g, i_layerName, i_replaceImage);
	}
	else if (hasColorizeOverlay() && i_g->Get3D())
	{
		Color overlay = getOverlayEffectsColor();
		RenderEffect* effect = i_g->Get3D()->GetEffect(g_colorizeEffect);
		effect->SetCurrentTechnique("Default", true);
		float params[4];
		params[0] = std::min(overlay.GetRed() * (1.0f / 255.0f), 255.0f);
		params[1] = std::min(overlay.GetGreen() * (1.0f / 255.0f), 255.0f);
		params[2] = std::min(overlay.GetBlue() * (1.0f / 255.0f), 255.0f);
		params[3] = std::min(overlay.GetAlpha() * (1.0f / 255.0f), 255.0f);
		effect->SetVector4("Params", params);
		for (RenderEffectAutoState state(i_g, effect, 1); state; ++state)
			m_pam->DrawReplaceLayerWithImage(i_g, i_layerName, i_replaceImage);
	}
	else if (hasMultiplicativeOverlay() && i_g->Get3D())
	{
		Color overlay = getOverlayEffectsColor();
		RenderEffect* effect = i_g->Get3D()->GetEffect(g_multiplicativeEffect);
		effect->SetCurrentTechnique("Default", true);
		float params[4];
		params[0] = std::min(overlay.GetRed() * (1.0f / 255.0f), 255.0f);
		params[1] = std::min(overlay.GetGreen() * (1.0f / 255.0f), 255.0f);
		params[2] = std::min(overlay.GetBlue() * (1.0f / 255.0f), 255.0f);
		params[3] = std::min(overlay.GetAlpha() * (0.5f / 255.0f), 255.0f);
		effect->SetVector4("Params", params);
		for (RenderEffectAutoState state(i_g, effect, 1); state; ++state)
			m_pam->DrawReplaceLayerWithImage(i_g, i_layerName, i_replaceImage);
	}
	else if (m_saturation < 1.0f && i_g->Get3D())
	{
		RenderEffect* effect = i_g->Get3D()->GetEffect(g_desaturateEffect);
		effect->SetCurrentTechnique("Default", true);
		effect->SetFloat("Saturation", m_saturation);
		for (RenderEffectAutoState state(i_g, effect, 1); state; ++state)
			m_pam->DrawReplaceLayerWithImage(i_g, i_layerName, i_replaceImage);
	}
	else
	{
		m_pam->DrawReplaceLayerWithImage(i_g, i_layerName, i_replaceImage);
	}
	onPostDraw(i_g);
}

bool PopAnimRig::Serialize(const RtSerializeContext& inContext)
{
	bool result = inContext.GetSync()->SyncBeginObject(RtSerialRtonKey("pamobjdata"));
	if (result)
	{
		if (inContext.GetSync()->IsWriting())
		{
			RtId pamId = m_pam->GetRtId();
			inContext.GetSync()->SyncRtId(RtSerialRtonKey("PamRtId"), pamId);
		}
		if (inContext.GetSync()->IsReading())
		{
			RtId pamId;
			inContext.GetSync()->SyncRtId(RtSerialRtonKey("PamRtId"), pamId);
			m_pam = RtDb::GetDb()->GetObjectForId(pamId)->Cast<PopAnim>()->Duplicate();
			m_pam->SetupSpriteInst("");
			m_pam->mListener = this;
			m_pam->mTransDirty = true;
		}
		inContext.GetSync()->SyncFloat(RtSerialRtonKey("mDrawScale"), m_pam->mDrawScale);
		inContext.GetSync()->SyncInt32(RtSerialRtonKey("mAnimRate"), m_pam->mAnimRate);
		inContext.GetSync()->SyncString(RtSerialRtonKey("mLastPlayedFrameLabel"), m_pam->mLastPlayedFrameLabel);
		inContext.GetSync()->SyncFloat(RtSerialRtonKey("mBlendTicksTotal"), m_pam->mBlendTicksTotal);
		inContext.GetSync()->SyncFloat(RtSerialRtonKey("mBlendTicksCur"), m_pam->mBlendTicksCur);
		inContext.GetSync()->SyncFloat(RtSerialRtonKey("mBlendDelay"), m_pam->mBlendDelay);
		SexyTransform2D& transform = m_pam->mTransform;
		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
				inContext.GetSync()->SyncFloat(RtSerialRtonKey(StrFormat("mTransform_%d_%d", row, col)), transform.m[row][col]);
		}
		Color& color = m_pam->mColor;
		for (int i = 0; i < 4; i++)
		{
			if (inContext.GetSync()->IsReading())
			{
				int value;
				inContext.GetSync()->SyncInt32(RtSerialRtonKey(StrFormat("mColor_%d", i)), value);
				color[i] = value;
			}
			else
			{
				int value = color[i];
				inContext.GetSync()->SyncInt32(RtSerialRtonKey(StrFormat("mColor_%d", i)), value);
			}
		}
		inContext.GetSync()->SyncBool(RtSerialRtonKey("mAdditive"), m_pam->mAdditive);
		inContext.GetSync()->SyncBool(RtSerialRtonKey("mAnimRunning"), m_pam->mAnimRunning);
		inContext.GetSync()->SyncBool(RtSerialRtonKey("mPaused"), m_pam->mPaused);
		if (inContext.GetSync()->IsReading())
		{
			float currentFrame;
			inContext.GetSync()->SyncFloat(RtSerialRtonKey("CurrentFrame"), currentFrame);
			PASpriteInst* mainInst = m_pam->mMainSpriteInst;
			mainInst->mDelayFrames = 0;
			mainInst->mFrameRepeats = 0;
			mainInst->mFrameNum = currentFrame;
			uint32 count;
			inContext.GetSync()->SyncBeginArray(RtSerialRtonKey("HiddenLayers"), count);
			for (uint32 i = 0; i < count; i++)
			{
				std::string layerName;
				inContext.GetSync()->SyncString(RtSerialRtonKey(""), layerName);
				SetLayerVisibility(layerName, false);
			}
			inContext.GetSync()->SyncEndArray();
		}
		else
		{
			inContext.GetSync()->SyncFloat(RtSerialRtonKey("CurrentFrame"), m_pam->mMainSpriteInst->mFrameNum);
			std::queue<PASpriteInst*> spriteQueue;
			std::set<std::string> hiddenNames;
			spriteQueue.push(m_pam->mMainSpriteInst);
			while (!spriteQueue.empty())
			{
				PASpriteInst* spriteInst = spriteQueue.front();
				spriteQueue.pop();
				if (!spriteInst->mSpriteVisibility)
					hiddenNames.insert(spriteInst->mDef->mExportName);
				for (size_t i = 0; i < spriteInst->mChildren.size(); i++)
				{
					if (spriteInst->mChildren[i].mSpriteInst != NULL)
						spriteQueue.push(spriteInst->mChildren[i].mSpriteInst);
				}
			}
			std::vector<std::string> hiddenLayers(hiddenNames.begin(), hiddenNames.end());
			uint32 count = hiddenLayers.size();
			inContext.GetSync()->SyncBeginArray(RtSerialRtonKey("HiddenLayers"), count);
			for (int i = 0; i < count; i++)
				inContext.GetSync()->SyncString(RtSerialRtonKey(""), hiddenLayers[i]);
			inContext.GetSync()->SyncEndArray();
		}
		inContext.GetSync()->SyncEndObject();
		GameObject::Serialize(inContext);
	}
	return result;
}

void PopAnimRig::SetPopAnimCommandDelegate(PopAnimCommandDelegate i_onPopAnimCommand)
{
	m_onPopAnimCommand = i_onPopAnimCommand;
}

void PopAnimRig::SetPopAnimCommandDelegate(PopAnimCommandReflectionDelegate i_onPopAnimCommand)
{
	m_serialOnPopAnimCommand = i_onPopAnimCommand;
}

void PopAnimRig::SetAudioObject(RtWeakPtr<BoardEntity> i_audioObj)
{
	m_audioObject = i_audioObj;
}

AnimHandle PopAnimRig::PlayAndStop(const std::string& i_animLabel, AnimSelectionMethod i_select, AnimStoppedDelegate i_onAnimStopped)
{
	AnimHandle handle = Play(i_animLabel, PLAY_ONCE, i_select);
	if (handle != ANIMHANDLE_NONE)
	{
		clearPlaybackDelegates();
		m_onAnimStopped = i_onAnimStopped;
	}
	return handle;
}

AnimHandle PopAnimRig::PlayAndStop(const std::string& i_animLabel, AnimSelectionMethod i_select, AnimStoppedReflectionDelegate i_onAnimStopped)
{
	AnimHandle handle = Play(i_animLabel, PLAY_ONCE, i_select);
	if (handle != ANIMHANDLE_NONE)
	{
		clearPlaybackDelegates();
		m_serialOnAnimStopped = i_onAnimStopped;
	}
	return handle;
}

AnimHandle PopAnimRig::PlayAndContinue(const std::string& i_animLabel, AnimSelectionMethod i_select, LoopingAnimContinuedDelegate i_onLoopingAnimContinued)
{
	AnimHandle handle = Play(i_animLabel, PLAY_CONTINUOUS, i_select);
	if (handle != ANIMHANDLE_NONE)
	{
		clearPlaybackDelegates();
		m_onLoopingAnimContinued = i_onLoopingAnimContinued;
	}
	return handle;
}

AnimHandle PopAnimRig::PlayAndContinue(const std::string& i_animLabel, AnimSelectionMethod i_select, LoopingAnimContinuedReflectionDelegate i_onLoopingAnimContinued)
{
	AnimHandle handle = Play(i_animLabel, PLAY_CONTINUOUS, i_select);
	if (handle != ANIMHANDLE_NONE)
	{
		clearPlaybackDelegates();
		m_serialOnLoopingAnimContinued = i_onLoopingAnimContinued;
	}
	return handle;
}

AnimHandle PopAnimRig::BlendTo(const std::string& i_animLabel, float i_blendTime, float i_blendDelay, AnimPlayStyle i_playStyle, AnimSelectionMethod i_select, AnimStoppedDelegate i_onAnimStopped)
{
	std::string labelToPlay;
	if (selectVariation(i_animLabel, i_select, labelToPlay, m_activeAnimLastPlayedVariation, std::vector<int>()))
	{
		int variation = m_activeAnimLastPlayedVariation;
		if (m_pam->BlendTo(labelToPlay, i_blendTime, i_blendDelay))
		{
			fireInterrupts(labelToPlay, variation);
			m_activeAnimPlayStyle = i_playStyle;
			m_activeAnimSelectMethod = i_select;
			m_activeAnim = (AnimHandle)(m_activeAnim + 1);
			m_activeAnimBaseLabel = i_animLabel;
			m_activeAnimSeqEndCount = 0;
			m_onAnimStopped = i_onAnimStopped;
			return m_activeAnim;
		}
	}
	return ANIMHANDLE_NONE;
}

AnimHandle PopAnimRig::BlendTo(const std::string& i_animLabel, float i_blendTime, float i_blendDelay, AnimPlayStyle i_playStyle, AnimSelectionMethod i_select, AnimStoppedReflectionDelegate i_onAnimStopped)
{
	std::string labelToPlay;
	if (selectVariation(i_animLabel, i_select, labelToPlay, m_activeAnimLastPlayedVariation, std::vector<int>()))
	{
		int variation = m_activeAnimLastPlayedVariation;
		if (m_pam->BlendTo(labelToPlay, i_blendTime, i_blendDelay))
		{
			fireInterrupts(labelToPlay, variation);
			m_activeAnimPlayStyle = i_playStyle;
			m_activeAnimSelectMethod = i_select;
			m_activeAnim = (AnimHandle)(m_activeAnim + 1);
			m_activeAnimBaseLabel = i_animLabel;
			m_activeAnimSeqEndCount = 0;
			m_serialOnAnimStopped = i_onAnimStopped;
			return m_activeAnim;
		}
	}
	return ANIMHANDLE_NONE;
}

void PopAnimRig::SetLayerVisibility(const std::vector<std::string>& i_layerNames, bool i_visible)
{
	for (std::vector<std::string>::const_iterator it = i_layerNames.begin(), end = i_layerNames.end(); it != end; ++it)
	{
		std::string layerName = *it;
		getPAM()->mMainSpriteInst->SetSpriteVisibility(layerName, i_visible);
	}
}

void PopAnimRig::SetLayerVisibilityByIndex(const std::vector<std::string>& i_layers, int i_index)
{
	int index = ClampInt(i_index, 0, i_layers.size() - 1);
	for (size_t i = 0; i < i_layers.size(); i++)
		SetLayerVisibility(i_layers[i], (int)i == index);
}

void PopAnimRig::SetLayerVisibilityByIndex(const std::vector<std::vector<std::string> >& i_layers, int i_index)
{
	int index = ClampInt(i_index, 0, i_layers.size() - 1);
	for (size_t i = 0; i < i_layers.size(); i++)
	{
		if ((int)i != index)
			SetLayerVisibility(i_layers[i], false);
	}
	SetLayerVisibility(i_layers[i_index], true);
}

void PopAnimRig::SetLayerVisibilityByPercent(const std::vector<std::vector<std::string> >& i_layers, float i_percent)
{
	SetLayerVisibilityByIndex(i_layers, (int)(i_percent / (1.0f / ((float)i_layers.size() - 1.0f))));
}
