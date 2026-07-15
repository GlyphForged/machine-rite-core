# Machine Rite Core

This is my attempt at building a simple, reusable library. Not trying to re-invent the wheel, none of these are better than the commonly used options, there are many like them, but these are mine. I've come to realize that relying on LLMs as a learning tool was a mistake, so I'm re-starting by leveraging resources like Beej's guide to C, man pages, and old stack exchange posts. The way Ada and Alan would have wanted it, probably.

## Scrolls (Dynamic Arrays)

First project will be a dynamic array. No one taking the time to read this needs it explained by me. I'm going with the name "scroll" rather than the traditional 'vector' partly for thematic reasons (something something Tech Priest something something) and because if you squint and tilt your head you can kinda see how a scroll can  be seen as a dynamic list of information. I did say you had to squint.

To consider these complete, I figure they should have the following functionality:

- Init & Purge functionality to create and destroy scrolls.
- Push/Pop functionality (Push -> "Ink"? Thematic and shorter)
- Insert/Remove functionality (Insert -> "Graft"? Remove -> "Redact"? Might be a bit ambiguous...)
- Scan for non-destructive data access
- Len(gth) and Cap(acity) for metadata access. ("Span" and "Limit"?)
- MAYBE: Trim to free up memory when a scroll has much less data than capacity.

Notes:
- I really like the idea of my scrolls pulling double duty, so I plan to add push/pop for stack-like behavior (FILO), and then the typical insert/remove behavior. I'd love to have it pull triple duty, but from what I'm reading ring buffers might be the better way to handle queue-like behavior, so I may have to revisit that.
- In my mental model of a dynamic array, the expectation is that the data is mutable, as such, I'm going to default to destructive behaviors. Should anyone be deranged enough to use these libs beyond myself, expectation is that you are using methods like "Peek" to access data nondestructively.
