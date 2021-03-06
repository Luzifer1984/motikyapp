//
//  MTLModel.h
//  Mantle
//
//  Created by Justin Spahr-Summers on 2012-09-11.
//  Copyright (c) 2012 GitHub. All rights reserved.
//

#import <Foundation/Foundation.h>

// An abstract base class for model objects, using reflection to provide
// sensible default behaviors.
//
// The default implementations of <NSCopying>, -hash, and -isEqual: make use of
// the +propertyKeys method.
@interface MTLModel : NSObject <NSCopying>

// Returns a new instance of the receiver initialized using
// -initWithDictionary:.
+ (instancetype)modelWithDictionary:(NSDictionary *)dictionaryValue;

// Initializes the receiver with default values.
//
// This is the designated initializer for this class.
- (instancetype)init;

// Initializes the receiver using key-value coding, setting the keys and values
// in the given dictionary. If `dictionaryValue` is nil, this method is equivalent
// to -init.
//
// Any NSNull values will be converted to nil before being used. KVC validation
// methods will be automatically invoked for all of the properties given.
//
// Returns an initialized model object, or nil if validation failed.
- (instancetype)initWithDictionary:(NSDictionary *)dictionaryValue;

// Returns the keys for all @property declarations, except for `readonly`
// properties without ivars, or properties on MTLModel itself.
+ (NSSet *)propertyKeys;

// A dictionary representing the properties of the receiver.
//
// The default implementation combines the values corresponding to all
// +propertyKeys into a dictionary, with any nil values represented by NSNull.
//
// This property must never be nil.
@property (nonatomic, copy, readonly) NSDictionary *dictionaryValue;

// Merges the value of the given key on the receiver with the value of the same
// key from the given model object, giving precedence to the other model object.
//
// By default, this method looks for a `-merge<Key>FromModel:` method on the
// receiver, and invokes it if found. If not found, and `model` is not nil, the
// value for the given key is taken from `model`.
- (void)mergeValueForKey:(NSString *)key fromModel:(MTLModel *)model;

// Merges the values of the given model object into the receiver, using
// -mergeValueForKey:fromModel: for each key in +propertyKeys.
//
// `model` must be an instance of the receiver's class or a subclass thereof.
- (void)mergeValuesForKeysFromModel:(MTLModel *)model;

@end

@interface MTLModel (Unavailable)

+ (instancetype)modelWithExternalRepresentation:(NSDictionary *)externalRepresentation __attribute__((deprecated("Replaced by -[MTLJSONAdapter initWithJSONDictionary:modelClass:]")));
- (instancetype)initWithExternalRepresentation:(NSDictionary *)externalRepresentation __attribute__((deprecated("Replaced by -[MTLJSONAdapter initWithJSONDictionary:modelClass:]")));

@property (nonatomic, copy, readonly) NSDictionary *externalRepresentation __attribute__((deprecated("Replaced by MTLJSONAdapter.JSONDictionary")));

+ (NSDictionary *)externalRepresentationKeyPathsByPropertyKey __attribute__((deprecated("Replaced by +JSONKeyPathsByPropertyKey in <MTLJSONSerializing>")));
+ (NSValueTransformer *)transformerForKey:(NSString *)key __attribute__((deprecated("Replaced by +JSONTransformerForKey: in <MTLJSONSerializing>")));

+ (NSDictionary *)migrateExternalRepresentation:(NSDictionary *)externalRepresentation fromVersion:(NSUInteger)fromVersion __attribute__((deprecated("Replaced by -decodeValueForKey:withCoder:modelVersion:")));

@end
