#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayer.h>

typedef NS_ENUM(NSUInteger, TTTPlayerMovieScalingMode) {
    TTTPlayerMovieScalingModeNone,       // No scaling
    TTTPlayerMovieScalingModeAspectFit,  // Uniform scale until one dimension fits
    TTTPlayerMovieScalingModeAspectFill, // Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
    TTTPlayerMovieScalingModeFill        // Non-uniform scale. Both render dimensions will exactly match the visible bounds
};

/**
 TTTPlayer 的可选配置类，在初始化 TTTPlayer 对象的时候传入其实例进行 TTTPlayer 的可选项配置
 */
@interface TTTPlayerOptions : NSObject

@property (nonatomic, assign) TTTPlayerMovieScalingMode movieScalingMode;

/**
 使用默认配置生成一个 TTTPlayerOption 对象
 */
+ (nonnull TTTPlayerOptions *)defaultOptions;

@end
