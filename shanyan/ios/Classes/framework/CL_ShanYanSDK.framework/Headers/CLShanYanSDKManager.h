//
//  CLShanYanSDKManager.h
//  CL_ShanYanSDK
//
//  Created by wanglijun on 2018/10/29.
//  Copyright © 2018 wanglijun. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "CLCompleteResult.h"

@protocol CLShanYanSDKManagerDelegate <NSObject>
@optional
//暂无代理回调
@end

NS_ASSUME_NONNULL_BEGIN
@interface CLShanYanSDKManager : NSObject

/// 设置点击协议代理
/// @param delegate 代理
+ (void)setCLShanYanSDKManagerDelegate:(id<CLShanYanSDKManagerDelegate>)delegate;

/**
 初始化
 @param appId 闪验后台申请的appId
 @param complete 预初始化回调block 
 */
+(void)initWithAppId:(NSString *)appId complete:(nullable CLComplete)complete;

///**
// 设置初始化超时 单位:s
// 大于0有效
// 建议4s左右，默认4s
// */
//+ (void)setInitTimeOut:(NSTimeInterval)initTimeOut;

/**
 设置预取号超时 单位:s
 大于0有效
 建议4s左右，默认4s
 */
+ (void)setPreGetPhonenumberTimeOut:(NSTimeInterval)preGetPhoneTimeOut;


/// 当无蜂窝网络（拔出SIM卡/切换SIM卡,网络切换期间/或者直接关闭流量开关）是否使用之前的取号缓存
/// @param isUseCache YES/NO  默认YES   设置为NO  获取SIM实时的预取号，无蜂窝网络、或者蜂窝网络不稳定则无法取号成功
+ (void)setPreGetPhonenumberUseCacheIfNoCellularNetwork:(BOOL)isUseCache;

/**
 * 预取号
 * 此调用将有助于提高闪验拉起授权页的速度和成功率
 * 建议在一键登录前提前调用此方法，比如调一键登录的vc的viewdidload中
 * 不建议在拉起授权页后调用
 * ⚠️‼️以 if (completeResult.error == nil) 为判断成功的依据，而非返回码
 * ⚠️‼️此方法回调队列为dispatch_get_global_queue(0, 0)，回调中如需UI操作，请自行切到主线程
 * ⚠️‼️预取号成功后，脱敏手机号相关信息在completeResult.data中获取：
 * number：脱敏手机号（必须在授权页显示此脱敏手机号）
 * telecom：预取号时的当前运营商类型，CTCC：电信、CMCC：移动、CUCC：联通
 * protocolName：运营商协议名称（必须在授权页显示此运营商协议，且可查看协议详情）
 * protocolUrl：运营商协议链接（用于查看运营商协议web页详情，配合protocolName使用）
 * ⚠️其余字段可忽略
 * 预取号成功时completeResult示例：
 * {
     code = 1000,
     innerDesc = "cache",
     message = "电信预取号成功",
     data =     {
         protocolName = "天翼账号服务与协议",
         telecom = "CTCC",
         cl_config_expiredTime = 3590,
         number = "173****4253",
         protocolUrl = "https://cmcc.cn/protocol/agreement",
         telecomChannel = 2,
     },
     innerCode = 1000,
 }
 */
+(void)preGetPhonenumber:(nullable CLComplete)complete;

/**************一键登录获取Token***************/
/// 注：此方法回调队列为dispatch_get_global_queue(0, 0)，如需UI操作请自行切入主线程
+(void)loginAuth:(CLComplete)complete;




/**************本机认证(本机号码校验)***************/
+ (void)mobileCheckWithLocalPhoneNumberComplete:(CLComplete)complete;




/**************SDK功能方法***************/
/**
 模式控制台日志输出控制（默认关闭）
 @param enable 开关参数
 */
+ (void)printConsoleEnable:(BOOL)enable;


/// 获取当前流量卡运营商，结果仅供参考
// CTCC：电信、CMCC：移动、CUCC：联通、UNKNOW：未知
+ (NSString *)getOperatorType;

+ (void)clearScripCache;

/**
 禁止日志上报(默认开启)
 ****此接口需要在初始化之前调用,否则配置不生效****
 @param forbidden YES:禁止上报 NO:允许上报
 */
+ (void)forbiddenFullLogReport:(BOOL)forbidden;

+(void)sdkInit:(NSString *)appId complete:(nullable CLComplete)complete;

+ (BOOL)checkAuthEnable;

/**
 * 当前SDK版本号
 */
+ (NSString *)clShanYanSDKVersion;
@end

NS_ASSUME_NONNULL_END
